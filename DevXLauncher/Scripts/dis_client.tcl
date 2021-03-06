##########################################################################
# Copyright (c) 2015, Synopsys, Inc.                                     #
# All rights reserved.                                                   #
#                                                                        #
# Redistribution and use in source and binary forms, with or without     #
# modification, are permitted provided that the following conditions are #
# met:                                                                   #
#                                                                        #
# 1. Redistributions of source code must retain the above copyright      #
# notice, this list of conditions and the following disclaimer.          #
#                                                                        #
# 2. Redistributions in binary form must reproduce the above copyright   #
# notice, this list of conditions and the following disclaimer in the    #
# documentation and/or other materials provided with the distribution.   #
#                                                                        #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    #
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      #
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  #
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   #
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, #
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       #
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  #
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  #
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    #
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  #
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   #
##########################################################################
# This is the startup file for dev. express. 
# (wish -f $DIS_INSTALL/dis_client.tcl Service), which 
# starts dish by pipe
# communcates with dish and editor, including error handling
# builds ui

set startup 0
cd $env(DIS_INSTALL)
source common_init.tcl
source split_pane.tcl
source tree.tcl
source dialog.tcl
source combobox.tcl
namespace import ::combobox::*
source util.tcl
source editor_cmds.tcl
source psetlite.tcl
source ui.tcl
source error_browser.tcl
source notebook.tcl
source submit_check.tcl
source appClient.tcl

set Service [lindex $argv 0]

if {![regexp \[0-9\.\]*@\[a-zA-Z0-9\._-\]+ $Service]} {
    set error 1
    source $env(DIS_INSTALL)/ServiceChooser.tcl
    tkwait window .w
    exit
}

if {[regsub {^@} $Service {} s_name]} {
	set available_hosts {}
	set available_hosts [exec $Dish -all]
	if { $available_hosts == "" } {
		tk_messageBox -title {Error} -message {Can not connect to any hosts} -type ok -icon error 
		exit
	} else {
		# this will fill a list of all services on the network
		# in the following format : hostip@service_name
		set available_service ""
	    foreach computer $available_hosts {
			set ip   [lindex $computer 0]
	        set service_list [join [exec $Dish -test $ip]]
			foreach s $service_list {
				if { $s == $s_name} {
					set available_service "$ip@$s"
			  		break
				}
			}
			if { $available_service != "" } {
				break
			}
		}
	}
    if { $available_service == "" } {
		set error 1
		source $env(DIS_INSTALL)/ServiceChooser.tcl
		tkwait window .w
		exit
	}
set Service $available_service
}

set_service_tag 0
global Transform
global opened_modelflist
global opened_localflist

if { [info exists env(DIS_CONNECTION)] && $env(DIS_CONNECTION)=="http"}  {
    # We are using HTTP connection - we will use server src root.
    set Transform 2
	set CM 0
	set scope_flag 0
    set ModelSrcRoot ""
    set SharedSrcRoot ""
    set PrivateSrcRoot ""
    set opened_modelflist {}
    set opened_localflist {}
    regsub -all {\\} $PrivateSrcRoot / PrivateSrcRoot
    set name [string trimright $PrivateSrcRoot "/"]
    set PrivateSrcRoot "$name/"
	tempdirectory_init
} else {
    # Lan -  we will try to read data from the file
    if { [file exists $env(HOME)/dislite/$Model_name/$Model_name.prefs] } {
        init_setting $env(HOME)/dislite/$Model_name/$Model_name.prefs
    } else {
        set error 1
        source $env(DIS_INSTALL)/ServiceChooser.tcl
        tkwait window .w
        exit
    }
}

set strip_service $Service
regsub -all {\\} $strip_service _ strip_service
regsub -all {/} $strip_service _ strip_service
regsub -all {:} $strip_service _ strip_service
if [isunix] {
    set temp $Tempdir/$env(USER).$strip_service
} else {
    set temp $Tempdir/$strip_service
}
set session 1
while { [file exists $temp.$session] } {
    incr session
}
set Tempdirectory $temp.$session
file mkdir $Tempdirectory

source group.tcl

if $CM {
    source cm.tcl
}

proc error_check {} {
    global env Service Tempdirectory error Model_name error_file
    if {[file exists $error_file]} {
	if {[file size $error_file]>0} {
	    set f [open $error_file]
	    gets $f line
	    close $f
	    myputs "Dislite_Error {Error: $line}"
	    set error 1
	    catch {destroy .d1}
	    do_prefs
	    file_delete $Tempdirectory
	    exit
	}
    }
}

proc dis_wait { fn} {
    set lock ${fn}.lock
    while {! [file exists $lock] } {
	    error_check 
	    after 25 
    }
    return [file_delete $lock]
}


set connected 0

proc read_file { fn } {
global Tempdirectory
global connected
global Service

   set res ""
   if {[gets $fn length]<0} {
        if { $connected == 0 } {
            startup_error
		} else {
            tk_messageBox -title {Connection Error} -message {Server is shutting down.} -type ok -icon error 
	        set Service ""
		    do_exit 0
		}
   }

   while { $length > 0 } {
      if { [gets $fn line]<0 } {
        if { $connected == 0 } {
            startup_error
		} else {
            tk_messageBox -title {Connection Error} -message {Server is shutting down.} -type ok -icon error 
	        set Service ""
		    do_exit 0
		}
	  }
      lappend res $line
      set length [expr $length-1]
   }
   set connected 1
   return $res
}

set cur_ind 0
set max_ind 0
proc dis_get_next_ind {} {
    global cur_ind max_ind result
    if {$cur_ind && ![llength $result($cur_ind)]} {
	return $cur_ind
    }
    if {$cur_ind == 20 } {
	set cur_ind 0
    }
    incr cur_ind
    if {$cur_ind > $max_ind } {
	set max_ind $cur_ind
    }
    return $cur_ind
}
proc query_command_internal { cmd } {
    debug_msg $cmd
    global result dis_ofile dis_in 
    error_check
    change_cursor watch
    update idletasks
    set ind [dis_get_next_ind]
    set cmd [list browser_query $ind $cmd]
    puts $dis_in $cmd; flush $dis_in
    set result($ind) [read_file $dis_in]
	set res {}
	set tags {}
    foreach el $result($ind) {
	    set sep [string first "\t" $el]
		set to [expr $sep-1]
		set from [expr $sep+1]
		lappend res  [string range $el 0 $to]
		lappend tags [string range $el $from end]
    }
	set result($ind) $res
    set result(tags_$ind) $tags
    set result(sel_$ind) {}
    change_cursor ""
    return $result($ind)
}

proc query_command { cmd } {
    global list
    set res [query_command_internal $cmd]
    $list delete 0 end
    foreach el $res {
	    $list insert end $el 
    }
    status_line [$list size]
}

proc dis_command {args} {
    dis_cmd [join $args]
}

proc dis_cmd cmd {
  
    debug_msg $cmd
    global dis_ofile dis_in 
    error_check
	global aseticons20
    if $aseticons20 {
	   set full_cmd "set_printformat 1;"
    } else {
	   set full_cmd "set_printformat 0;"
    }
	append full_cmd $cmd;
    puts $dis_in $full_cmd; 
	flush $dis_in
    set x [read_file $dis_in]
	return $x
}
proc dis_print { set {att {}}} {
    dis_cmd [list dis_print $set $att]
}
proc dis_query { cmd {att {}}} {
    dis_cmd [list dis_query $cmd $att]
}

proc copy_result_to_file { cmd file } {
    global dis_in

	set ret 1
    puts $dis_in $cmd; 
	flush $dis_in
    set buf [read_file $dis_in ]
	set f [open $file w]
	foreach el $buf {
	   puts $f $el
	}
	close $f
	return $ret
}

proc read_pipe {} {
    set input_str [gets stdin]
    ReadPipe $input_str
}

# note : position could be offset or line,col
proc ReadPipe {input_str} {
    set cmd [lindex $input_str 0]
    set local_fname [change_drivename [lindex $input_str 1]]
    switch -exact -- $cmd {
	pid_reply { ed_pid_reply }
	save_hook { ed_save_hook $local_fname }
	kill_hook { ed_kill_hook $local_fname }
	exit_hook { do_emacsexit }
	activate  { activate_browser }
	cmput_reply { global bufmodified; set bufmodified [lindex $input_str 2] }
	editor_get { ed_get $local_fname }
	default {
	    if {![string compare $cmd "right_click"]} {
		after 300 { myputs "Emacs_Menu" }
	    } 
	    set offset [lindex $input_str 2]
	    set line [lindex $input_str 3]
	    set col [lindex $input_str 4]
	    set n [get_index $local_fname 1]	    
	    if {$n<0} {return}
	    set position [get_model_position $local_fname $n $offset $line $col]
	    if {$position==""} { return }
	    global opened_modelflist 
	    set model_fname [lindex $opened_modelflist $n]
	    switch -exact -- $cmd {
		inst_def { ed_describe $model_fname $position }
		query { ed_query $model_fname $position }
		open_def { ed_open_def $model_fname $position }
		instances { ed_instances $model_fname $position }
		right_click { ed_describe $model_fname $position }
	    }
	}
    }
}

if [isunix] {
    fileevent stdin readable read_pipe
} else {
    start_readthread
}   

proc dis_start { service } {

    set pos [string first "@" $service]
	if { $pos == -1 } {
	   set host ""
	   set service_name $service
	} else {
	   set host [string range $service 0 [expr $pos-1]]
	   set service_name [string range $service [expr $pos+1] end]
	}
    
    global dis_ofile dis_in Tempdirectory Tempdir error_file
    global env Psethome Dish Service Model_name
    set dis_ofile [tempfile $Tempdirectory dis]
    if [isunix] {
	set error_file $Tempdirectory/$Service.err
    } else {
	set error_file [tempfile $Tempdir $Service.err]
    }
    if ![file executable $Dish] {
	write "Dislite_Error {Error: Cannot find dish $Dish}"
	tk_messageBox -title {Error} -message "Cannot find dish $Dish" -type ok -icon error
	file_delete $Tempdirectory
	do_exit 0 
    }
    file_delete $error_file
	global Transform
	global ModelSrcRoot
	global PrivateSrcRoot
	global SharedSrcRoot
	if {$host == ""} {
        set dis_in [open "| $Dish $service_name -dislite -s dis_server.tcl" r+]
	} else {
        if { [info exists env(DIS_CONNECTION)] && $env(DIS_CONNECTION)=="http"}  {
           set dis_in [open "| $Dish $service_name -http $host -dislite -s dis_server.tcl" r+]
		} else {
           set dis_in [open "| $Dish $service_name -connect $host -dislite -s dis_server.tcl" r+]
 	    }
	}
	# if no license available on the server all commands will fail
    set res [dis_command set x aaa]
	if { $res != "aaa" } {
        tk_messageBox -title {License error} -message {No licenses available on the selected server} -type ok -icon error 
        global connected
		if { $connected == 0 } {
            startup_error
		} else {
		    do_exit 0
		}

    }
    return 1
}

proc discope { service } {
    global aseticons20

    set w .d1
    set m $w.mbar
    set n $w.toolbar
    set t $w.top
    set b $w.bot
    set s $w.stat
    set e $w.ent

    image create bitmap idir -file fl_folder.xbm    

    catch {destroy $w}
    toplevel $w -class Dialog
    wm geometry $w =600x500
    wm minsize $w 450 100
    wm title $w "Discover $service"

    wm protocol $w WM_DELETE_WINDOW do_exit

    frame $n -relief groove  -bd 1
    if [isunix] {
	set relief groove
    } else {
	set relief sunken
    }
    frame $t -width 300 -height 400  -relief $relief -bd 1
    frame $s -relief raised -bd 1 
    pack $s  -side bottom -fill both
    pack $n -side top -fill x 
    pack $t -side top -fill both -expand true

    if ![isunix] {
	set relief raised
    }
    
    set t1 $t.left
    set t2 $t.right
    frame $t1
    frame $t2

    source menu80.tcl	
    build_toolbar $n $relief
    build_menu $m
    
    build_leftpanel $t1
    build_listbox $t2
    Pane_Create $t1 $t2 -in $t -percent 0.33

    build_statusline $s

    if $aseticons20 {
	dis_command set_printformat 1
    } else {
	dis_command set_printformat 0
    }
    after 150
    init_projbrowser
    activate_browser
    myputs "Dislite_Loaded"
    tkwait window $w
}

wm withdraw .
dis_start $Service
discope $Service

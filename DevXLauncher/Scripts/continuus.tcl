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
set driver "C"
if [string length $SharedSrcRoot] {
   set driver [string index $SharedSrcRoot 0]
}
   
proc cm_get_src { cm_sysfile cm_workfile $comment } {
    global Tempdirectory
    set cm_comment $Tempdirectory/cm_comment.tmp
    set f [open $cm_comment]
	puts -nonewline $f $comment
	close $f
    cm_exec_command configtool co -cf \"$cm_comment\" "$cm_workfile"
}

proc cm_unget_src { cm_sysfile cm_workfile } {
    cm_exec_command configtool unco "$cm_workfile"
}

proc cm_put_src { cm_sysfile cm_workfile comment } {
    global Tempdirectory
    set cm_comment $Tempdirectory/cm_comment.tmp
    set f [open $cm_comment]
	puts -nonewline $f $comment
	close $f
    cm_exec_command configtool ci -cf \"$cm_comment\" "$cm_workfile"
}

proc cm_local_list {} {
    global driver Transform
	global PrivateSrcRoot
    if {!$Transform} {
	    cd ${driver}:/
    }
    set filelist [cm_pipe_list configtool lsco $PrivateSrcRoot]
    cm_list_command cm_file_filter $filelist
}  
proc cm_pipe_list { args } {
    global Tempdirectory
    set cm_err $Tempdirectory/cm_err.out
    set err [ catch { open "| $args 2>$cm_err " } pp ]
    set linelist {}
    if { $err } {
	   set f [open $cm_err]
	   set msg [read $f]
	   close $f
    } else {
	while { ! [eof $pp] } {
	    set line [gets $pp]
	    set line [string toupper $line]
	    lappend linelist $line
	}
	close $pp
    }

	set slinelist {}
	foreach x $linelist {
	   set short [string range $x 2 end]
       regsub -all {\\} $short {/} short
	   if { $short != "" } {
	      lappend slinelist $short
		}
	}
    return $slinelist
}
proc cm_get_view {} {
    set err [cm_exec_command ss whoami]
    if {!$err} {
	    global cm_exec_msg
	    return $cm_exec_msg
    }
    return ""
}


proc ccmSelectTask {} {
#	ccm.exe task /default /g
	cm_exec_command configtool exec -e SelectDefaultTask
}

proc ccmTaskCheckIn {} {
#	ccm.exe create_task /g
	cm_exec_command configtool exec -e CheckInDefaultTask
}

proc ccmTaskCreate {} {
#	ccm.exe ci /g /task ""
	cm_exec_command configtool exec -e CreateDefaultTask
}
proc ccmTaskReconfigure {} {
	set arglist [dis_prepare_selection]

	# if no selection in listbox or selection is tree node, don't do anything
	if {[llength $arglist]<1} {
		tk_messageBox -title "CM Message" -message "You need to select a project to Reconfigure." -type ok -icon error
		return
	}

	set flist [dis_command apply fname $arglist]
	if { [llength $flist]==1 } {
		set flist [lindex $flist 0]
	}
	foreach ff $flist {
#		exec ccm.exe reconfigure $ff /g
		cm_exec_command configtool exec -e reconfigure $ff
	    }
}
proc ccmTaskReconcile {} {
	set arglist [dis_prepare_selection]

	# if no selection in listbox or selection is tree node, don't do anything
	if {[llength $arglist]<1} {
		tk_messageBox -title "CM Message" -message "You need to select a project to Reconcile." -type ok -icon error
		return
	}

	set flist [dis_command apply fname $arglist]
	if { [llength $flist]==1 } {
		set flist [lindex $flist 0]
	}
	foreach ff $flist {
#		exec ccm.exe reconcile2 $ff /g
		cm_exec_command configtool exec -e reconcile $ff
	    }
}

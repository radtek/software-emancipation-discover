PATHTOROOT=../../..
MAKESCRIPTSPATH=$(PATHTOROOT)/makescripts/Windows
include $(MAKESCRIPTSPATH)/defs.mak
 
LIBRARY=$(INTDIR)/stream_message.lib

OBJS= \
	$(INTDIR)/msg_comms.obj \
	$(INTDIR)/msg_format.obj \
	$(INTDIR)/minidom.obj \
	$(INTDIR)/minixml.obj \
	$(INTDIR)/minisax.obj \
	$(INTDIR)/aconnectn.obj \
	$(INTDIR)/mbmsgser.obj \
	$(INTDIR)/mbuildmsg.obj \
	$(INTDIR)/service.obj \
	$(INTDIR)/startprocess.obj \
	$(INTDIR)/transport.obj

VPATH=$(PATHTOROOT)/stream_message/src;$(PATH2BS)/stream_message/src

CPP_INCLUDES=\
	/I $(PATHTOROOT)/stream_message/include \
	/I $(PATH2BS)/stream_message/include \
	/I $(PATHTOROOT)/nameserver/include \
	/I $(PATH2BS)/nameserver/include

CPP_PROJ=/MD\
 $(CPP_OPTS)\
 $(CPP_WINDOWS)\
 $(CPP_DEFINES)\
 $(CPP_INCLUDES)\
 $(CPP_FINISH)

include $(MAKESCRIPTSPATH)/targets.mak


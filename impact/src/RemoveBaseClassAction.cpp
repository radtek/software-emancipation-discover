/*************************************************************************
* Copyright (c) 2015, Synopsys, Inc.                                     *
* All rights reserved.                                                   *
*                                                                        *
* Redistribution and use in source and binary forms, with or without     *
* modification, are permitted provided that the following conditions are *
* met:                                                                   *
*                                                                        *
* 1. Redistributions of source code must retain the above copyright      *
* notice, this list of conditions and the following disclaimer.          *
*                                                                        *
* 2. Redistributions in binary form must reproduce the above copyright   *
* notice, this list of conditions and the following disclaimer in the    *
* documentation and/or other materials provided with the distribution.   *
*                                                                        *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    *
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      *
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  *
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   *
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       *
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  *
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  *
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  *
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   *
*************************************************************************/
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/LabelG.h>

#include "RemoveBaseClassAction.h"
#include "ComboBox.h"

CRemoveBaseClassAction::CRemoveBaseClassAction():CImpactAction("Remove Base Class"){
	m_ClassesList = NULL;
	m_pClasses = NULL;
}

CRemoveBaseClassAction::~CRemoveBaseClassAction() {
	m_ClassesList=NULL;
	if(m_pClasses != NULL) delete m_pClasses;
}

Widget CRemoveBaseClassAction::GetAttributesArea(Widget parent, symbolPtr* pSym){
	XmString labelStr;
	Widget area = XtVaCreateWidget("area", 
		xmFormWidgetClass, parent,
		XmNwidth, 300,
		XmNheight, 30,
		XmNnumColumns, 2,
		XmNpacking, XmPACK_COLUMN,
		XmNorientation, XmVERTICAL,
		NULL);
	string result;
	string command;
	string id = prepareQuery(CEntityInfo::etag(pSym));

	setWait(true);
        command = "printformat \"%s\t%s\" name etag;";
        if(CEntityInfo::language(pSym).compare("JAVA")==0) {
        	command = string("sort [filter class&&name!=\"Object\" [get_super_classes ") + id +string("]]");
        } else {
        	command = string("sort [get_super_classes ") + id + string("]");
        }
	CEntityInfo::exec(command,result);
	m_pClasses = new CQueryResult(); 
	m_pClasses->parse(result); 	
	if(m_pClasses->getRecordsCount()>0) {
		labelStr = XmStringCreateLocalized("Base Class:");
		Widget labelWidget = XtVaCreateManagedWidget("label_1",xmLabelGadgetClass, area,
			XmNlabelString, labelStr,
			XmNwidth, 100,
			XmNtopAttachment,XmATTACH_FORM, 
			XmNleftAttachment,XmATTACH_FORM,
			XmNbottomAttachment,XmATTACH_FORM, 
			NULL);
		XmStringFree(labelStr);
		m_ClassesList = XtVaCreateManagedWidget("classeslist",
			        dtComboBoxWidgetClass, area,
				XmNtopAttachment,XmATTACH_FORM, 
				XmNleftAttachment,XmATTACH_WIDGET,
				XmNleftWidget, labelWidget,
				XmNrightAttachment,XmATTACH_FORM, 
				XmNbottomAttachment,XmATTACH_FORM, 
				NULL);

		TRecordSetIterator iter = m_pClasses->getStartRecord();
		TRecordSetIterator end = m_pClasses->getEndRecord();
		while(iter!=end) {
			TRecord* pRecord = *iter;
			labelStr = XmStringCreateLocalized((char*)(*pRecord)[1]->c_str());
			DtComboBoxAddItem(m_ClassesList, labelStr, 0, false);
			XmStringFree(labelStr);
			iter++;
		}
	}  else {
		labelStr = XmStringCreateLocalized("Nothing to remove.");
		Widget labelWidget = XtVaCreateManagedWidget("label_1",xmLabelGadgetClass, area,
			XmNlabelString, labelStr,
			XmNwidth, 100,
			XmNtopAttachment,XmATTACH_FORM, 
			XmNleftAttachment,XmATTACH_FORM,
			XmNbottomAttachment,XmATTACH_FORM, 
			XmNrightAttachment,XmATTACH_FORM, 
			NULL);
		XmStringFree(labelStr);
	}

	setWait(false);
	
	return area;
}

bool CRemoveBaseClassAction::ActionPerformed(symbolPtr* pSym) {
  
  if(m_pClasses->getRecordsCount()>0) {
	CImpactAction::ActionPerformed(pSym);
  	  
	int selectedPosition;
	XtVaGetValues(m_ClassesList, XmNselectedPosition, &selectedPosition, NULL);
	TRecord* pRecord = m_pClasses->getRecord(selectedPosition);
	string command = "Impact:RemoveBaseClass " + prepareQuery(CEntityInfo::etag(pSym)) + " " + prepareQuery(*(*pRecord)[1]);

  	SetDescription(GetName()+string(" ")+*(*pRecord)[0]);

	string results;
	CEntityInfo::exec(command,results);
	parseResult(results);
 	return true;
  } else 
	return false;
}


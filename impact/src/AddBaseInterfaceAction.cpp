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

#include "AddBaseInterfaceAction.h"
#include "ComboBox.h"

CAddBaseInterfaceAction::CAddBaseInterfaceAction():CImpactAction("Implement Interface"){
	m_InterfacesList = NULL;
  	m_pAvailable = NULL;
	m_pImplemented = NULL;
}

CAddBaseInterfaceAction::~CAddBaseInterfaceAction() {
	m_InterfacesList=NULL;
	if(m_pAvailable != NULL) delete m_pAvailable;
	if(m_pImplemented != NULL) delete m_pImplemented;
}

Widget CAddBaseInterfaceAction::GetAttributesArea(Widget parent, symbolPtr* pSym){
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

	setWait(true);

	// lets get the implemented interfaces first
	command = "query_closure 50 \"get_super_classes\" " + prepareQuery(CEntityInfo::etag(pSym));
	CEntityInfo::exec("printformat \"%s\t%s\" etag kind;source_dis closure.dis",result);
	CEntityInfo::exec(command,result);
	m_pImplemented = new CQueryResult(); 
	m_pImplemented->parse(result); 	

	// now get all available interfaces
	command = "printformat \"%s\t%s\" name etag;sort name [defines -interfaces /]";
	CEntityInfo::exec(command,result);
	m_pAvailable = new CQueryResult(); 
	m_pAvailable->parse(result); 	

	if(m_pAvailable->getRecordsCount()>0 ) {
		labelStr = XmStringCreateLocalized("Interface:");
		Widget labelWidget = XtVaCreateManagedWidget("label_1",xmLabelGadgetClass, area,
			XmNlabelString, labelStr,
			XmNwidth, 100,
			XmNtopAttachment,XmATTACH_FORM, 
			XmNleftAttachment,XmATTACH_FORM,
			XmNbottomAttachment,XmATTACH_FORM, 
			NULL);
		XmStringFree(labelStr);
		m_InterfacesList = XtVaCreateManagedWidget("interfaceslist",
			        dtComboBoxWidgetClass, area,
				XmNtopAttachment,XmATTACH_FORM, 
				XmNleftAttachment,XmATTACH_WIDGET,
				XmNleftWidget, labelWidget,
				XmNrightAttachment,XmATTACH_FORM, 
				XmNbottomAttachment,XmATTACH_FORM, 
				NULL);

		TRecordSetIterator iter = m_pAvailable->getStartRecord();
		TRecordSetIterator end = m_pAvailable->getEndRecord();
		CQueryResult DeletedRecords;
		while(iter!=end) {
			TRecord* pRecord = *iter;
			TField* field = (*pRecord)[2];
			if(!m_pImplemented->contains(*field,1)) {
				labelStr = XmStringCreateLocalized((char*)(*pRecord)[1]->c_str());
				DtComboBoxAddItem(m_InterfacesList, labelStr, 0, false);
				XmStringFree(labelStr);
			} else
				DeletedRecords.add(pRecord);
			iter++;
		}
		iter = DeletedRecords.getStartRecord();
		end = DeletedRecords.getEndRecord();
		while(iter!=end) {
			TRecord* pRecord = *iter;
			m_pAvailable->remove(pRecord);
			iter++;
		}
	} else {
		cout << "Nothing to Implement" << endl;
		labelStr = XmStringCreateLocalized("Nothing to implement.");
                Widget labelWidget = XtVaCreateManagedWidget("label_1",
			xmLabelGadgetClass, area,
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

bool CAddBaseInterfaceAction::ActionPerformed(symbolPtr* pSym) {
 
 if (m_pAvailable->getRecordsCount() > 0 ) { 
  	CImpactAction::ActionPerformed(pSym);
  
  	int selectedPosition;
  	XtVaGetValues(m_InterfacesList, XmNselectedPosition, &selectedPosition, NULL);

  	TRecord* pRecord = m_pAvailable->getRecord(selectedPosition);

  	SetDescription(GetName()+string(" ")+*(*pRecord)[1]);

  	string command = "Impact:AddBaseInterface " + prepareQuery(CEntityInfo::etag(pSym)) + " " + prepareQuery(*(*pRecord)[2]);

  	string results;
  	CEntityInfo::exec(command,results);
  	parseResult(results);
  	return true;
  } else {
	return false;
  }
}

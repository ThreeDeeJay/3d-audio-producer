#include "listener-track.h"

ListenerTrack::ListenerTrack(const wxString& title) : Track(title)
{
	listenerToManipulatePtr = nullptr;
	
	//initialize tracks
	xTrack = new DoubleTrack("X Track");
	yTrack = new DoubleTrack("Y Track");
	zTrack = new DoubleTrack("Z Track");
	
	tempX = 0.0; tempY=0.0; tempZ=0.0;
	
	xTrack->SetReferenceToVarToManipulate(&tempX);
	yTrack->SetReferenceToVarToManipulate(&tempY);
	zTrack->SetReferenceToVarToManipulate(&tempZ);
	
	
	Connect(wxEVT_PAINT, wxPaintEventHandler(Track::OnPaint));
	Connect(wxEVT_SIZE, wxSizeEventHandler(Track::OnSize));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(DoubleTrack::OnLeftMouseClick));
	Connect(wxEVT_CONTEXT_MENU, wxCommandEventHandler(DoubleTrack::OnRightMouseClick));
	
}

void ListenerTrack::FunctionToCallInPlayState()
{
	xTrack->FunctionToCallInPlayState();
	yTrack->FunctionToCallInPlayState();
	zTrack->FunctionToCallInPlayState();
	
	float thisX = float(tempX);
	float thisY = float(tempY);
	float thisZ = float(tempZ);
		
	if(listenerToManipulatePtr != nullptr)
	{
		if(!listenerToManipulatePtr->GetListenerFreeRoamBool())
		{
			if(listenerToManipulatePtr->getPositionX() != thisX){listenerToManipulatePtr->setPositionX(thisX);}
		
			if(listenerToManipulatePtr->getPositionY() != thisY){listenerToManipulatePtr->setPositionY(thisY);}
			
			if(listenerToManipulatePtr->getPositionZ() != thisZ){listenerToManipulatePtr->setPositionZ(thisZ);}			
		}
		
	}
}

void ListenerTrack::FunctionToCallInPauseState(){}
void ListenerTrack::FunctionToCallInRewindState(){}
void ListenerTrack::FunctionToCallInFastForwardState(){}
void ListenerTrack::FunctionToCallInNullState(){}

void ListenerTrack::SetReferenceToListenerToManipulate(Listener* thisListener){listenerToManipulatePtr = thisListener;}

DoubleTrack* ListenerTrack::GetReferenceToXTrack(){return xTrack;}
DoubleTrack* ListenerTrack::GetReferenceToYTrack(){return yTrack;}
DoubleTrack* ListenerTrack::GetReferenceToZTrack(){return zTrack;}


void ListenerTrack::InitTrack(wxWindow* parent, std::vector <int> *timeTickVector)
{
		
}	

void ListenerTrack::SetupAxisForVariable(double& start, double& end,double& resolution, int& numTick)
{
	xTrack->SetupAxisForVariable(start,end,resolution,numTick);
	yTrack->SetupAxisForVariable(start,end,resolution,numTick);
	zTrack->SetupAxisForVariable(start,end,resolution,numTick);
	
}

void ListenerTrack::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	
	xTrack->render(dc);
	yTrack->render(dc);
	zTrack->render(dc);
	
}

void ListenerTrack::OnScroll(wxScrollEvent& event)
{
	Refresh();
	
	FitInside();
	
}

void ListenerTrack::OnSize(wxSizeEvent& event)
{
	Refresh();
	
	FitInside();
	
}
		
void ListenerTrack::SetReferenceToCurrentTimeVariable(double* thisTimeVariable)
{
	Track::SetReferenceToCurrentTimeVariable(thisTimeVariable);
	
	xTrack->SetReferenceToCurrentTimeVariable(thisTimeVariable);
	yTrack->SetReferenceToCurrentTimeVariable(thisTimeVariable);
	zTrack->SetReferenceToCurrentTimeVariable(thisTimeVariable);
}

void ListenerTrack::SetReferenceToTimeTickVector(std::vector <int> *thisVector)
{
	Track::SetReferenceToTimeTickVector(thisVector);
	xTrack->SetReferenceToTimeTickVector(thisVector);
	yTrack->SetReferenceToTimeTickVector(thisVector);
	zTrack->SetReferenceToTimeTickVector(thisVector);
}

std::vector <int> *ListenerTrack::GetReferenceToTimeTickVector(){return Track::GetReferenceToTimeTickVector();}

double ListenerTrack::GetCurrentTime(){return Track::GetCurrentTime();}
		
void ListenerTrack::OnLeftMouseClick(wxMouseEvent& event)
{
	xTrack->logic_left_click();
	yTrack->logic_left_click();
	zTrack->logic_left_click();
	event.Skip();
}

void ListenerTrack::OnRightMouseClick(wxCommandEvent& event)
{
	xTrack->logic_right_click();
	yTrack->logic_right_click();
	zTrack->logic_right_click();
	event.Skip();
}


#include "CustomNode4.h"

VISUAL_NODE_CHILD_CPP(CustomNode4)

CustomNode4::CustomNode4() : FEVisualNode()
{
	Type = "CustomNode4";

	SetStyle(FE_VISUAL_NODE_STYLE_DEFAULT);

	SetSize(ImVec2(370, 130));
	SetName("CustomNode4");

	TitleBackgroundColor = ImColor(128, 117, 208);
	TitleBackgroundColorHovered = ImColor(135, 145, 255);
	
	AddInputSocket(new FEVisualNodeSocket(this, FE_NODE_SOCKET_FLOAT_CHANNEL_IN, "in"));
}

CustomNode4::CustomNode4(const CustomNode4& Src) : FEVisualNode(Src)
{
	Data = Src.Data;

	SetStyle(FE_VISUAL_NODE_STYLE_DEFAULT);
}

void CustomNode4::SetStyle(FE_VISUAL_NODE_STYLE NewValue)
{
	// Do nothing. We don't want to change style
}

void CustomNode4::Draw()
{	
	FEVisualNode::Draw();

	ImVec2 NodePosition = ImGui::GetCursorScreenPos();
	ImVec2 NodeSize = GetSize();

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(55.0f, 50.0f));
	ImGui::Text("Node demonstrate socket events");

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(55.0f, 70.0f));
	std::string OutputText = "Last socket event: \n" + LastSocketEventDiscription;
	ImGui::Text(OutputText.c_str());
}

void CustomNode4::SocketEvent(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* ConnectedSocket, FE_VISUAL_NODE_SOCKET_EVENT EventType)
{
	FEVisualNode::SocketEvent(OwnSocket,  ConnectedSocket, EventType);

	std::string EventTypeStr = "Unknown";
	switch (EventType)
	{
		case FE_VISUAL_NODE_SOCKET_CONNECTED:
			EventTypeStr = "Connected";
		break;

		case FE_VISUAL_NODE_SOCKET_DISCONNECTED:
			EventTypeStr = "Disconnected";
		break;

		case FE_VISUAL_NODE_SOCKET_DESTRUCTION:
			EventTypeStr = "Destruction";
		break;

		case FE_VISUAL_NODE_SOCKET_UPDATE:
			EventTypeStr = "Update";
		break;
	}

	LastSocketEventDiscription = "Node ID: " + ConnectedSocket->GetParent()->GetID() + "\nEvent type: " + EventTypeStr;
}

float CustomNode4::GetData()
{
	return Data;
}

bool CustomNode4::CanConnect(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* CandidateSocket, char** MsgToUser)
{
	if (!FEVisualNode::CanConnect(OwnSocket, CandidateSocket, nullptr))
		return false;

	return true;
}

FEVisualNode* CustomNode4::GetNextNode()
{
	if (Output.size() > 0 && Output[0]->GetConnections().size() > 0)
		return Output[0]->GetConnections()[0]->GetParent();
	
	return nullptr;
}
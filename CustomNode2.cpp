#include "CustomNode2.h"

VISUAL_NODE_CHILD_CPP(CustomNode2)

CustomNode2::CustomNode2() : FEVisualNode()
{
	Type = "CustomNode2";

	SetStyle(FE_VISUAL_NODE_STYLE_DEFAULT);

	SetSize(ImVec2(350, 120));
	SetName("CustomNode2");

	TitleBackgroundColor = ImColor(128, 117, 208);
	TitleBackgroundColorHovered = ImColor(135, 145, 255);
	
	AddOutputSocket(new FEVisualNodeSocket(this, FE_NODE_SOCKET_FLOAT_CHANNEL_OUT, "out"));
}

CustomNode2::CustomNode2(const CustomNode2& Src) : FEVisualNode(Src)
{
	Data = Src.Data;

	SetStyle(FE_VISUAL_NODE_STYLE_DEFAULT);
}

void CustomNode2::SetStyle(FE_VISUAL_NODE_STYLE NewValue)
{
	// Do nothing. We don't want to change style
}

void CustomNode2::Draw()
{	
	FEVisualNode::Draw();

	ImVec2 NodePosition = ImGui::GetCursorScreenPos();
	ImVec2 NodeSize = GetSize();

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 50.0f));
	ImGui::Text("This is custom node");

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 90.0f));
	ImGui::Text("This node can be connected to CustomNode3.");
}

void CustomNode2::SocketEvent(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* ConnectedSocket, FE_VISUAL_NODE_SOCKET_EVENT EventType)
{
	FEVisualNode::SocketEvent(OwnSocket,  ConnectedSocket, EventType);
}

float CustomNode2::GetData()
{
	return Data;
}

bool CustomNode2::CanConnect(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* CandidateSocket, char** MsgToUser)
{
	if (!FEVisualNode::CanConnect(OwnSocket, CandidateSocket, nullptr))
		return false;

	return false;
}

FEVisualNode* CustomNode2::GetNextNode()
{
	if (Output.size() > 0 && Output[0]->GetConnections().size() > 0)
		return Output[0]->GetConnections()[0]->GetParent();
	
	return nullptr;
}
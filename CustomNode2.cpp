#include "CustomNode2.h"

VISUAL_NODE_CHILD_CPP(CustomNode2)

CustomNode2::CustomNode2() : VisualNode()
{
	Type = "CustomNode2";

	SetStyle(VISUAL_NODE_STYLE_DEFAULT);

	SetSize(ImVec2(350, 120));
	SetName("CustomNode2");

	TitleBackgroundColor = ImColor(128, 117, 208);
	TitleBackgroundColorHovered = ImColor(135, 145, 255);
	
	AddSocket(new NodeSocket(this, "FLOAT", "out", true));
}

CustomNode2::CustomNode2(const CustomNode2& Src) : VisualNode(Src)
{
	Data = Src.Data;

	SetStyle(VISUAL_NODE_STYLE_DEFAULT);
}

void CustomNode2::SetStyle(VISUAL_NODE_STYLE NewValue)
{
	// Do nothing. We don't want to change style
}

void CustomNode2::Draw()
{	
	VisualNode::Draw();

	ImVec2 NodePosition = ImGui::GetCursorScreenPos();
	ImVec2 NodeSize = GetSize();

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 50.0f));
	ImGui::Text("This is custom node");

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 90.0f));
	ImGui::Text("This node can be connected to CustomNode3.");
}

void CustomNode2::SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, VISUAL_NODE_SOCKET_EVENT EventType)
{
	VisualNode::SocketEvent(OwnSocket,  ConnectedSocket, EventType);
}

float CustomNode2::GetData()
{
	return Data;
}

bool CustomNode2::CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser)
{
	if (!VisualNode::CanConnect(OwnSocket, CandidateSocket, nullptr))
		return false;

	return false;
}

VisualNode* CustomNode2::GetNextNode()
{
	if (Output.size() > 0 && Output[0]->GetConnections().size() > 0)
		return Output[0]->GetConnections()[0]->GetParent();
	
	return nullptr;
}
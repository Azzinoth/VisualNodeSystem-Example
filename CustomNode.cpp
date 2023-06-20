#include "CustomNode.h"

VISUAL_NODE_CHILD_CPP(CustomNode)

CustomNode::CustomNode() : FEVisualNode()
{
	Type = "CustomNode";
	bCouldBeDestroyed = false;

	SetStyle(FE_VISUAL_NODE_STYLE_DEFAULT);

	SetSize(ImVec2(220, 78));
	SetName("CustomNode");

	TitleBackgroundColor = ImColor(31, 117, 208);
	TitleBackgroundColorHovered = ImColor(35, 145, 255);
	
	AddOutputSocket(new FEVisualNodeSocket(this, FE_NODE_SOCKET_FLOAT_CHANNEL_OUT, "out"));
}

CustomNode::CustomNode(const CustomNode& Src) : FEVisualNode(Src)
{
	Data = Src.Data;
	bCouldBeDestroyed = false;

	SetStyle(FE_VISUAL_NODE_STYLE_DEFAULT);
}

void CustomNode::SetStyle(FE_VISUAL_NODE_STYLE NewValue)
{
	// Do nothing. We don't want to change style
}

void CustomNode::Draw()
{	
	FEVisualNode::Draw();

	ImVec2 NodePosition = ImGui::GetCursorScreenPos();
	ImVec2 NodeSize = GetSize();

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 34.0f));
	ImGui::Text("This is custom node");

	ImGui::SetCursorScreenPos(NodePosition + ImVec2(5.0f, 55.0f));
	ImGui::Text("User non-deletable node.");
}

void CustomNode::SocketEvent(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* ConnectedSocket, FE_VISUAL_NODE_SOCKET_EVENT EventType)
{
	FEVisualNode::SocketEvent(OwnSocket,  ConnectedSocket, EventType);
}

float CustomNode::GetData()
{
	return Data;
}

bool CustomNode::CanConnect(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* CandidateSocket, char** MsgToUser)
{
	if (!FEVisualNode::CanConnect(OwnSocket, CandidateSocket, nullptr))
		return false;

	return false;
}

FEVisualNode* CustomNode::GetNextNode()
{
	if (Output.size() > 0 && Output[0]->GetConnections().size() > 0)
		return Output[0]->GetConnections()[0]->GetParent();
	
	return nullptr;
}
#include "CustomNodeStyleDemonstration.h"

bool CustomNodeStyleDemonstration::isRegistered = []()
{
	NODE_FACTORY.RegisterNodeType("CustomNodeStyleDemonstration",
		[]() -> VisualNode* {
			return new CustomNodeStyleDemonstration();
		},

		[](const VisualNode& Node) -> VisualNode* {
			const CustomNodeStyleDemonstration& NodeToCopy = static_cast<const CustomNodeStyleDemonstration&>(Node);
			return new CustomNodeStyleDemonstration(NodeToCopy);
		}
	);

	return true;
}();

CustomNodeStyleDemonstration::CustomNodeStyleDemonstration() : VisualNode()
{
	Type = "CustomNodeStyleDemonstration";

	SetStyle(VISUAL_NODE_STYLE_DEFAULT);

	SetSize(ImVec2(160, 130));
	SetName("Style Demonstration");

	TitleBackgroundColor = ImColor(128, 117, 208);
	TitleBackgroundColorHovered = ImColor(135, 145, 255);

	// Socket type can be associated with color system wide.
	NODE_SYSTEM.AssociateSocketTypeToColor("BOOL", ImColor(0,0,225));
	NODE_SYSTEM.AssociateSocketTypeToColor("FLOAT", ImColor(0, 225, 0));
	NODE_SYSTEM.AssociateSocketTypeToColor("MARCHING_ANT", ImColor(0, 225, 225));
	
	AddSocket(new NodeSocket(this, "BOOL", "bool", false));
	AddSocket(new NodeSocket(this, "FLOAT", "float", false));
	AddSocket(new NodeSocket(this, "MARCHING_ANT", "ants", false));
	AddSocket(new NodeSocket(this, "FADE_OUT", "fade", false));

	AddSocket(new NodeSocket(this, "BOOL", "bool", true));
	AddSocket(new NodeSocket(this, "FLOAT", "float", true));
	AddSocket(new NodeSocket(this, "MARCHING_ANT", "ants", true));
	AddSocket(new NodeSocket(this, "FADE_OUT", "fade", true));

	// Also individual socket connections could have unique styles.
	VisualNodeConnectionStyle CurrentStyle;
	GetSocketStyle(true, 2, CurrentStyle);
	CurrentStyle.bMarchingAntsEffect = true;
	SetSocketStyle(true, 2, CurrentStyle);

	GetSocketStyle(true, 3, CurrentStyle);
	CurrentStyle.bPulseEffect = true;
	SetSocketStyle(true, 3, CurrentStyle);
}

CustomNodeStyleDemonstration::CustomNodeStyleDemonstration(const CustomNodeStyleDemonstration& Src) : VisualNode(Src)
{
	SetStyle(VISUAL_NODE_STYLE_DEFAULT);

	// Also individual socket connections could have unique styles.
	VisualNodeConnectionStyle CurrentStyle;
	GetSocketStyle(true, 2, CurrentStyle);
	CurrentStyle.bMarchingAntsEffect = true;
	SetSocketStyle(true, 2, CurrentStyle);

	GetSocketStyle(true, 3, CurrentStyle);
	CurrentStyle.bPulseEffect = true;
	SetSocketStyle(true, 3, CurrentStyle);
}

void CustomNodeStyleDemonstration::SetStyle(VISUAL_NODE_STYLE NewValue)
{
	// Do nothing. We don't want to change style
}

void CustomNodeStyleDemonstration::Draw()
{	
	VisualNode::Draw();

	bool LocalBool = CouldBeMoved();

	if (GetNodesConnectedToOutput().size() > 0)
	{
		ImVec2 NodePosition = ImGui::GetCursorScreenPos();
		VisualNodeConnectionStyle CurrentStyle;
		GetSocketStyle(true, 2, CurrentStyle);

		ImGui::SetCursorScreenPos(NodePosition + ImVec2(70.0f, 70.0f));
		if (ImGui::Checkbox("Reverse \ndirection", &bReverseDirection))
		{
			CurrentStyle.bMarchingAntsReverseDirection = bReverseDirection;
		}

		ImGui::SetCursorScreenPos(NodePosition + ImVec2(70.0f, 100.0f));
		ImGui::Text("Speed:");
		ImGui::SetCursorScreenPos(NodePosition + ImVec2(70.0f, 120.0f));
		ImGui::SetNextItemWidth(70.0f);
		ImGui::SliderFloat("##Speed", &CurrentStyle.MarchingAntsSpeed, 0.01f, 10.0f);

		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Speed of the marching ants effect");
			ImGui::EndTooltip();
			SetCouldBeMoved(false);
		}
		else
		{
			SetCouldBeMoved(true);
		}

		SetSocketStyle(true, 2, CurrentStyle);
	}
}

void CustomNodeStyleDemonstration::SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, VISUAL_NODE_SOCKET_EVENT EventType)
{
	VisualNode::SocketEvent(OwnSocket,  ConnectedSocket, EventType);
}

bool CustomNodeStyleDemonstration::CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser)
{
	if (!VisualNode::CanConnect(OwnSocket, CandidateSocket, nullptr))
		return false;

	return true;
}
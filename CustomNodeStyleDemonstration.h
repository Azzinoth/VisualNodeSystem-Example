#pragma once

#include "SubSystems/VisualNodeSystem/VisualNodeSystem.h"

class CustomNodeStyleDemonstration : public VisualNode
{
	friend class NodeFactory;
	static bool isRegistered;

	bool CanConnect(NodeSocket* OwnSocket, NodeSocket* CandidateSocket, char** MsgToUser);
	void SocketEvent(NodeSocket* OwnSocket, NodeSocket* ConnectedSocket, VISUAL_NODE_SOCKET_EVENT EventType);

	// Make it private
	void SetStyle(VISUAL_NODE_STYLE NewValue);

	std::string LastSocketEventDiscription = "None";

	bool bReverseDirection = false;
public:
	CustomNodeStyleDemonstration();
	CustomNodeStyleDemonstration(const CustomNodeStyleDemonstration& Src);

	void Draw();
};
#pragma once

#include "SubSystems/VisualNodeSystem/VisualNodeSystem.h"

class CustomNode3 : public VisNodeSys::Node
{
	friend class NodeFactory;
	static bool isRegistered;

	float Data = 0.0f;

	bool CanConnect(VisNodeSys::NodeSocket* OwnSocket, VisNodeSys::NodeSocket* CandidateSocket, char** MsgToUser);
	void SocketEvent(VisNodeSys::NodeSocket* OwnSocket, VisNodeSys::NodeSocket* ConnectedSocket, VisNodeSys::NODE_SOCKET_EVENT EventType);

	// Make it private
	void SetStyle(VisNodeSys::NODE_STYLE NewValue);
public:
	CustomNode3();
	CustomNode3(const CustomNode3& Src);

	void Draw();
	float GetData();
};
#pragma once

#include "SubSystems/FEVisualNodeSystem/FEVisualNodeSystem.h"

VISUAL_NODE_CHILD_PRIVATE_PART(CustomNode3)
	float Data = 0.0f;

	bool CanConnect(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* CandidateSocket, char** MsgToUser);
	void SocketEvent(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* ConnectedSocket, FE_VISUAL_NODE_SOCKET_EVENT EventType);

	// Make it private
	void SetStyle(FE_VISUAL_NODE_STYLE NewValue);
public:
	CustomNode3();
	CustomNode3(const CustomNode3& Src);

	void Draw();
	float GetData();

	FEVisualNode* GetNextNode();
};

VISUAL_NODE_CHILD_AFTER_CLASS(CustomNode3)
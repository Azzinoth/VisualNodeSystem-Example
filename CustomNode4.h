#pragma once

#include "SubSystems/FEVisualNodeSystem/FEVisualNodeSystem.h"

VISUAL_NODE_CHILD_PRIVATE_PART(CustomNode4)
	float Data = 0.0f;

	bool CanConnect(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* CandidateSocket, char** MsgToUser);
	void SocketEvent(FEVisualNodeSocket* OwnSocket, FEVisualNodeSocket* ConnectedSocket, FE_VISUAL_NODE_SOCKET_EVENT EventType);

	// Make it private
	void SetStyle(FE_VISUAL_NODE_STYLE NewValue);

	std::string LastSocketEventDiscription = "None";
public:
	CustomNode4();
	CustomNode4(const CustomNode4& Src);

	void Draw();
	float GetData();

	FEVisualNode* GetNextNode();
};

VISUAL_NODE_CHILD_AFTER_CLASS(CustomNode4)
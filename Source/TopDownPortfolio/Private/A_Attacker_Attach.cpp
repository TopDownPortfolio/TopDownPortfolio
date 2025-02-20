#include "A_Attacker_Attach.h"
#include "A_Character_Base.h"

AA_Attacker_Attach::AA_Attacker_Attach() :
	AA_Attacker{}, m_arCollisionData{}
{
}

void AA_Attacker_Attach::E_Init(AA_Character_Base* pOwner, FName strSocket)
{
	AA_Attacker::E_Init(pOwner, strSocket);
	USkeletalMeshComponent* pMesh = m_pOwner->GetMesh();
	m_arCollision.Reserve(m_arCollisionData.Num());
	for (FS_Attacker_AttachData& sData : m_arCollisionData)
	{
		UPrimitiveComponent* pComponent = Cast< UPrimitiveComponent>(AddComponentByClass(sData.cClass, false, FTransform{}, false));
		pComponent->AttachToComponent(pMesh, FAttachmentTransformRules::KeepRelativeTransform, sData.strAttachSocket);
		m_arCollision.Add(pComponent);
	}
}

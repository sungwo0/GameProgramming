using UnityEngine;

public class FollowCamera : MonoBehaviour
{
    public Transform target;   // 따라갈 대상 (Player)
    public Vector3 offset;     // 플레이어 기준 위치 오프셋
    public bool lockRotation = true;   // 회전 고정 여부

    void LateUpdate()
    {
        if (target == null) return;

        // 1) 위치만 따라가기
        transform.position = target.position + offset;

        // 2) 카메라 회전은 고정 (플레이어가 좌우로 움직여도 카메라 각도 안 변함)
        if (lockRotation)
        {
            // 원하는 각도 직접 고정 (예: 살짝 위에서 내려다보는 시점)
            transform.rotation = Quaternion.Euler(10f, 0f, 0f);
        }
    }
}

using UnityEngine;

public class FollowCamera : MonoBehaviour
{
    public Transform target;  // 따라갈 대상 (Player)
    public Vector3 offset;    // 상대 위치

    void LateUpdate()
    {
        if (target == null) return;

        transform.position = target.position + offset;
    }
}

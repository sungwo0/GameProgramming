using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    public float forwardSpeed = 5f;   // 앞으로 가는 속도
    public float sideSpeed = 4f;      // 좌우 이동 속도

    private Rigidbody rb;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    void FixedUpdate()
    {
        // 항상 앞으로(계단 방향) 이동
        Vector3 velocity = rb.velocity;
        velocity.z = forwardSpeed;  // Z 방향으로 전진 (계단이 Z+ 쪽에 있다고 가정)

        // 좌우 이동 (A/D 또는 방향키)
        float h = Input.GetAxisRaw("Horizontal"); // -1 ~ 1
        velocity.x = h * sideSpeed;

        rb.velocity = velocity;
    }
}

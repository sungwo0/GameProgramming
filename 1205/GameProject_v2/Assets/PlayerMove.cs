using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    [Header("기본 속도 설정")]
    public float baseForwardSpeed = 5f;   // 기본 앞으로 속도
    public float sideSpeed = 4f;          // 좌우 이동 속도

    [Header("난이도(속도 증가) 설정")]
    public float speedPerScore = 0.1f;    // 점수 1점당 속도 증가량
    public float maxForwardSpeed = 15f;   // 최대 앞으로 속도

    private Rigidbody rb;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    void FixedUpdate()
    {
        Vector3 velocity = rb.velocity;

        // 좌우 입력
        float h = Input.GetAxisRaw("Horizontal");
        velocity.x = h * sideSpeed;

        // 점수에 따라 앞으로 속도 계산
        float targetSpeed = baseForwardSpeed;

        // ScoreManager가 존재하면 점수 반영
        if (ScoreManager.Instance != null)
        {
            int score = ScoreManager.Instance.score;
            targetSpeed += score * speedPerScore;
        }

        // 최대 속도 제한
        if (targetSpeed > maxForwardSpeed)
        {
            targetSpeed = maxForwardSpeed;
        }

        velocity.z = targetSpeed;   // 앞으로 이동 속도 적용

        rb.velocity = velocity;
    }
}

using UnityEngine;

public class CoinCollect : MonoBehaviour
{
    public int scoreValue = 1;  // 코인 하나당 점수

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            // 점수 추가
            if (ScoreManager.Instance != null)
            {
                ScoreManager.Instance.AddScore(scoreValue);
            }

            // 코인 삭제
            Destroy(gameObject);
        }
    }
}

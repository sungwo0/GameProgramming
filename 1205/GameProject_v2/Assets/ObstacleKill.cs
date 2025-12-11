using UnityEngine;
using UnityEngine.SceneManagement;

public class ObstacleKill : MonoBehaviour
{
    public string gameOverSceneName = "GameOverScene";  // 동일하게

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.collider.CompareTag("Player"))
        {
            SceneManager.LoadScene(gameOverSceneName);
        }
    }
}

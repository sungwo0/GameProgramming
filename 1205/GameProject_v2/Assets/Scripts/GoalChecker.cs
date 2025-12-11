using UnityEngine;
using UnityEngine.SceneManagement;

public class GoalChecker : MonoBehaviour
{
    public Transform player;         // 플레이어 Transform
    public float goalHeight = 30f;   // 클리어 기준 높이(Y)
    public string clearSceneName = "ClearScene"; // 클리어 씬 이름

    private bool cleared = false;

    void Update()
    {
        if (cleared) return;
        if (player == null) return;

        // 플레이어가 목표 높이 이상 올라갔는지 체크
        if (player.position.y >= goalHeight)
        {
            cleared = true;
            SceneManager.LoadScene(clearSceneName);
        }
    }
}

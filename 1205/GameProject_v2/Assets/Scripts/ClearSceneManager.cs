using UnityEngine;
using UnityEngine.SceneManagement;

public class ClearSceneManager : MonoBehaviour
{
    public string gameSceneName = "계단게임씬"; // 메인 게임 씬 이름

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(gameSceneName);
        }
    }
}

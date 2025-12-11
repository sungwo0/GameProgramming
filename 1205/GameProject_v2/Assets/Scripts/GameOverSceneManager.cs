using UnityEngine;
using UnityEngine.SceneManagement;

public class GameOverSceneManager : MonoBehaviour
{
    public string gameSceneName = "StairGameScene";
    public string mainMenuSceneName = "MainMenuScene";

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(gameSceneName);
        }

        if (Input.GetKeyDown(KeyCode.M))
        {
            SceneManager.LoadScene(mainMenuSceneName);
        }
    }
}

using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenuManager : MonoBehaviour
{
    // 메인 게임 씬 이름 (네 실제 게임 씬 이름으로 바꿔야 함!)
    public string gameSceneName = "GameProject(업그레이드 후)";

    public void OnClickStart()
    {
        SceneManager.LoadScene(gameSceneName);
    }

    public void OnClickQuit()
    {
        // 에디터에서는 안 꺼짐, 빌드된 exe에서 종료됨
        Application.Quit();
        Debug.Log("Quit Game");
    }
}

using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class TitleSceneController : MonoBehaviour
{
    public Button GameStartButton;

    private void Start()
    {
        GameStartButton.onClick.AddListener(OnStartButtonClicked);
    }

    public void OnStartButtonClicked()
    {
        SceneManager.LoadScene("SelectStage");
    }
}

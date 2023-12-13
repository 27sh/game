using UnityEngine;
using UnityEngine.UI;

public class ExitButtonController : MonoBehaviour
{
    public Button exitButton;

    void Start()
    {
        if (exitButton != null)
        {
            exitButton.onClick.AddListener(OnExitButtonClick);
        }
    }

    void OnExitButtonClick()
    {
        Application.Quit();
    }
}

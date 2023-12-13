using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class BacktoTitle : MonoBehaviour
{
    public Button backButton;

    void Start()
    {
        if (backButton != null)
        {
            backButton.onClick.AddListener(OnBackButtonClicked);
        }
    }

    void OnBackButtonClicked()
    {
        SceneManager.LoadScene("TitleScene");
    }
}

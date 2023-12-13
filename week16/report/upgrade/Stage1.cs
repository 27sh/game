using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Stage1 : MonoBehaviour
{
    public Button button1;
    public Button button2;
    public Button button3;


    private void Start()
    {
        button1.onClick.AddListener(OnButton1Clicked);
        button2.onClick.AddListener(OnButton2Clicked);
        button3.onClick.AddListener(OnButton3Clicked);

    }

    public void OnButton1Clicked()
    {
        SceneManager.LoadScene("Stage1");
    }
    public void OnButton2Clicked()
    {
        SceneManager.LoadScene("Stage2");
    }
    public void OnButton3Clicked()
    {
        SceneManager.LoadScene("Stage3");
    }
}

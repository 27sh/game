using UnityEngine;
using UnityEngine.UI;

public class ButtonController : MonoBehaviour
{
    public PanelController associatedPanel;
    public Button button;

    void Start()
    {
        if (button != null)
        {
            button.onClick.AddListener(OnButtonClick);
        }
    }

    public void OnButtonClick()
    {
        if (associatedPanel != null)
        {
            if (associatedPanel.gameObject.activeSelf)
            {
                associatedPanel.ClosePanel();
            }
            else
            {
                associatedPanel.OpenPanel();
            }
        }
    }
}

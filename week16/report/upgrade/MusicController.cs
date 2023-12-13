using UnityEngine;
using UnityEngine.UI;

public class MusicController : MonoBehaviour
{
    private AudioSource audioSource;
    private static MusicController instance;
    public Slider volumeSlider;

    void Awake()
    {
        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    void Start()
    {
        audioSource = GetComponent<AudioSource>();

        PlayMusic();

        if (volumeSlider != null)
        {
            volumeSlider.onValueChanged.AddListener(OnVolumeChanged);
        }
    }

    void PlayMusic()
    {
        if (audioSource != null)
        {
            audioSource.Play();
        }
    }

    void OnVolumeChanged(float volume)
    {
        if (audioSource != null)
        {
            audioSource.volume = volume;
        }
    }
}

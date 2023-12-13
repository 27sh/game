using UnityEngine;
using UnityEngine.UI;

public class VolumeController : MonoBehaviour
{
    public AudioSource musicAudioSource;
    public Slider volumeSlider;

    void Start()
    {
        if (PlayerPrefs.HasKey("Music"))
        {
            float savedVolume = PlayerPrefs.GetFloat("Music");
            SetVolume(savedVolume);
        }
    }

    public void OnVolumeChanged()
    {
        float volume = volumeSlider.value;
        SetVolume(volume);
        PlayerPrefs.SetFloat("Music", volume);
    }

    void SetVolume(float volume)
    {
        if (musicAudioSource != null)
        {
            musicAudioSource.volume = volume;
        }
    }
}

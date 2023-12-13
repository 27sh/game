using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour
{
    public int move_method;
    public float speed;
    public Vector2 speed_vec;

    public GameObject particlePrefab;
    private int remainingItems;
    public PanelController clearPanelController;

    // Start is called before the first frame update
    void Start()
    {
        remainingItems = GameObject.FindGameObjectsWithTag("Item").Length;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Item"))
        {
            Destroy(collision.gameObject);
            remainingItems--;
                if (remainingItems <= 0)
                {
                    ShowClearPanel();
                }
        }
        else if (collision.CompareTag("Enemy"))
        {
            Dead();
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (move_method == 0)
        {
            speed_vec = Vector2.zero;

            if (Input.GetKey(KeyCode.RightArrow))
            {
                speed_vec.x += speed;
            }
            if (Input.GetKey(KeyCode.LeftArrow))
            {
                speed_vec.x -= speed;
            }
            if (Input.GetKey(KeyCode.UpArrow))
            {
                speed_vec.y += speed;
            }
            if (Input.GetKey(KeyCode.DownArrow))
            {
                speed_vec.y -= speed;
            }

            transform.Translate(speed_vec);
        }
        else if (move_method == 1)
        {
            speed_vec.x = Input.GetAxis("Horizontal") * speed;
            speed_vec.y = Input.GetAxis("Vertical") * speed;

            transform.Translate(speed_vec);
        }

        else if (move_method == 2)
        {
            speed_vec = Vector2.zero;

            if (Input.GetKey(KeyCode.RightArrow))
            {
                speed_vec.x += speed;
            }
            if (Input.GetKey(KeyCode.LeftArrow))
            {
                speed_vec.x -= speed;
            }
            if (Input.GetKey(KeyCode.UpArrow))
            {
                speed_vec.y += speed;
            }
            if (Input.GetKey(KeyCode.DownArrow))
            {
                speed_vec.y -= speed;
            }

            GetComponent<Rigidbody2D>().velocity = speed_vec;
        }

        if (Input.GetKeyDown(KeyCode.R))
        {
            Restart();
        }
    }

    public void Dead()
    {
        Destroy(gameObject);

        if (particlePrefab != null)
        {
            StartCoroutine(ShowGameOverPanelAfterParticle());
        }
    }

    IEnumerator ShowGameOverPanelAfterParticle()
    {
        Instantiate(particlePrefab, transform.position, Quaternion.identity);
        yield return new WaitForSeconds(1f);
    }

    public void Restart()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
    void ShowClearPanel()
    {
        if (clearPanelController != null)
        {
            clearPanelController.OpenPanel();
        }
    }
}

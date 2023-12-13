using UnityEngine;

public class EnemyController : MonoBehaviour
{
    public float speed = 5f;
    private Vector2 direction = Vector2.right;

    void Update()
    {
        MoveEnemy();
    }

    void MoveEnemy()
    {
        transform.Translate(direction * speed * Time.deltaTime);
    }

    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.CompareTag("Wall"))
        {
            ChangeDirection();
        }
    }

    void ChangeDirection()
    {
        direction = -direction;
    }
}

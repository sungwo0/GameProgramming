using System.Collections.Generic;
using UnityEngine;

public class InfiniteStairManager : MonoBehaviour
{
    public GameObject stairPrefab;      // 계단 프리팹
    public Transform player;            // 플레이어 Transform

    public int initialStairCount = 30;  // 처음에 몇 칸 생성할지
    public float stepHeight = 0.3f;     // 한 계단 올라갈 때 Y 증가량
    public float stepDepth = 1f;        // 한 계단 앞으로 갈 때 Z 증가량

    public float spawnDistanceAhead = 20f;   // 플레이어 앞쪽 몇 m까지 계단을 유지할지
    public float deleteDistanceBehind = 10f; // 플레이어 뒤쪽 얼마 이상 멀어지면 삭제할지

    private Queue<GameObject> stairs = new Queue<GameObject>();
    private Vector3 nextSpawnPos;

    public GameObject coinPrefab;     // 코인 프리팹
    [Range(0f, 1f)]
    public float coinSpawnChance = 0.3f;  // 계단 하나당 코인 생성 확률 (0~1)

    public GameObject obstaclePrefab;     // 장애물 프리팹
    [Range(0f, 1f)]
    public float obstacleSpawnChance = 0.2f;  // 계단 하나당 장애물 생성 확률 (0~1)

    void Start()
{
    if (stairPrefab == null || player == null)
    {
        Debug.LogError("InfiniteStairManager: stairPrefab 또는 player가 비어 있습니다!");
        enabled = false;
        return;
    }

    // 프리팹의 Collider 기준으로 자동 간격 맞추기
    var col = stairPrefab.GetComponent<Collider>();
    if (col != null)
    {
        var size = col.bounds.size;   // 실제 월드 크기
        stepHeight = size.y;          // 계단 높이
        stepDepth = size.z;           // 계단 깊이 (앞뒤)
        // 필요하면 약간 여유를 주고 싶으면 stepDepth = size.z * 1.05f; 이런 식으로
    }

    nextSpawnPos = transform.position;

    for (int i = 0; i < initialStairCount; i++)
    {
        SpawnOneStep();
    }
}


    void Update()
    {
        // 1) 플레이어 앞쪽에 계단이 충분한지 확인하면서 계속 생성
        while (nextSpawnPos.z - player.position.z < spawnDistanceAhead)
        {
            SpawnOneStep();
        }

        // 2) 뒤에 너무 멀어진 계단은 삭제
        if (stairs.Count > 0)
        {
            GameObject firstStep = stairs.Peek();
            if (player.position.z - firstStep.transform.position.z > deleteDistanceBehind)
            {
                Destroy(firstStep);
                stairs.Dequeue();
            }
        }
    }

    void SpawnOneStep()
{
    GameObject step = Instantiate(stairPrefab, nextSpawnPos, Quaternion.identity);
    stairs.Enqueue(step);

    // 계단 위에 코인 생성 (확률적으로)
    if (coinPrefab != null && Random.value < coinSpawnChance)
    {
        // 계단 위 살짝 위로 띄운 위치 계산
        Vector3 coinPos = nextSpawnPos;
        coinPos.y += 1.0f; // 계단 윗면 위로 약간 올리기 (필요에 따라 조절)

        Instantiate(coinPrefab, coinPos, Quaternion.identity);
    }

    // 장애물 생성 (확률)
    if (obstaclePrefab != null && Random.value < obstacleSpawnChance)
    {
        Vector3 obstaclePos = nextSpawnPos;
        // 계단 윗면 가운데에 놓되, 플레이어가 지나가는 높이 정도로 올리기
        obstaclePos.y += 0.5f; // 계단 높이에 맞게 필요하면 조정

        Instantiate(obstaclePrefab, obstaclePos, Quaternion.identity);
    }

    // 다음 계단 위치
    nextSpawnPos.y += stepHeight;
    nextSpawnPos.z += stepDepth;
}

}

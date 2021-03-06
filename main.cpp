#include <bangtal.h>
#include <stdio.h>
#include <math.h>


SceneID scene;
TimerID timer;
ObjectID button1, button2, button3;
ObjectID ground, column1, column2, column3;
ObjectID disks[10];

int arr[3][10];
int indices[3];
int N = 7;

int action[1024][2];

int t = 0;



void timerCallback(TimerID timer) {
    int from = action[t][0];
    int to = action[t][1];

    locateObject(disks[arr[from][indices[from] - 1] - 1], scene, 130 + 400 * to, 240 + indices[to] * 20);
    arr[to][indices[to]] = arr[from][indices[from] - 1];
    arr[from][indices[from] - 1] = 0;
    indices[from]--;
    indices[to]++;
    t++;
    if (t < pow(2, N) - 1) {
        setTimer(timer, 0.1f);
        startTimer(timer);
    }
}

void move(int from, int to) {
    action[t][0] = from;
    action[t][1] = to;
    t++;
}

void hanoi(int n, int from, int by, int to) {
    if (n == 1) {
        move(from, to);
    }
    else {
        hanoi(n - 1, from, to, by);
        move(from, to);
        hanoi(n - 1, by, from, to);
    }
}

void start() {
    indices[0] = N;
    indices[1] = 0;
    indices[2] = 0;

    for (int i = 0; i < 10; i++) {
        if (i < N) arr[0][i] = N - i;
        else arr[0][i] = 0;
        arr[1][i] = 0;
        arr[2][i] = 0;
    }

    hideObject(button1);
    hideObject(button2);
    hideObject(button3);

    t = 0;
    hanoi(N, 0, 1, 2);
    t = 0;
    setTimer(timer, 0.1f);
    startTimer(timer);
}

void increase() {
    if (N >= 10) return;
    N++;
    showObject(disks[N - 1]);
    for (int i = 0; i < N; i++) {
        locateObject(disks[i], scene, 130, 240 + (N - 1 - i) * 20);
    }
}

void decrease() {
    if (N <= 1) return;
    N--;
    hideObject(disks[N]);
    for (int i = 0; i < N; i++) {
        locateObject(disks[i], scene, 130, 240 + (N - 1 - i) * 20);
    }
}

void mouseCallBack(ObjectID id, int x, int y, MouseAction action) {
    if (id == button1) start();
    else if (id == button2) increase();
    else if (id == button3) decrease();
}

int main() {
    setTimerCallback(timerCallback);
    setMouseCallback(mouseCallBack);

    scene = createScene("hanoi", "Images/background.png");
    timer = createTimer();

    ground = createObject("Images/ground.png");
    locateObject(ground, scene, 0, 0);
    showObject(ground);

    column1 = createObject("Images/column.png");
    locateObject(column1, scene, 230, 240);
    showObject(column1);

    column2 = createObject("Images/column.png");
    locateObject(column2, scene, 630, 240);
    showObject(column2);

    column3 = createObject("Images/column.png");
    locateObject(column3, scene, 1030, 240);
    showObject(column3);


    button1 = createObject("Images/button1.png");
    locateObject(button1, scene, 780, 540);
    showObject(button1);

    button2 = createObject("Images/button2.png");
    locateObject(button2, scene, 930, 540);
    showObject(button2);

    button3 = createObject("Images/button3.png");
    locateObject(button3, scene, 1080, 540);
    showObject(button3);


    for (int i = 0; i < 10; i++) {
        char path[16];
        sprintf_s(path, "Images/%d.png", i + 1);
        disks[i] = createObject(path);
        locateObject(disks[i], scene, 130, 240 + (N - 1 - i) * 20);
        i < N ? showObject(disks[i]) : hideObject(disks[i]);
    }
    startGame(scene);
    return 0;
}

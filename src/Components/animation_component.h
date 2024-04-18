#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

struct AnimationComponent {
    int numFrames;
    int currentFrame;
    int frameRate;
    bool loop;

    AnimationComponent(int numFrames, int currentFrame, int frameRate, bool loop) {
        this->numFrames = numFrames;
        this->currentFrame = currentFrame;
        this->frameRate = frameRate;
        this->loop = loop;
    }
};


#endif
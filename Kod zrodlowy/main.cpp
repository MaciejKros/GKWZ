#include <SDL.h>
#include <iostream>
#include "Scene.h"
#include <vector>
#include "Camera.h"

using namespace std;

const double TRANSLATION = 5;
const double ROTATION = 0.05;
const double ZOOM = 0.05;
const int camWidth = 650;
const int camHeight = 650;

int main(int argc, char** argv) {
    double d=1;
    Camera cam(camWidth, camHeight);
    cam.scene.createTestScene();
    cam.scene.matrix.matr44 = cam.scene.matrix.getUnitMatrix();
    cam.scene.multiplyMatrixAndTriangleList();
    cam.scene.normalizeVisableTriangleList3dPoints();
    cam.scene.calculateAndSetVisableTriangleList();
    cam.scene.projectVisableTriangleListTo2d(d);
    cam.setTrianglesOnCamera();
    cam.setTrianglesBufferCoordinates();
    cam.paintScanLines();

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        SDL_Texture* texture = NULL;

        if (SDL_CreateWindowAndRenderer(camWidth, camHeight, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;
            SDL_Event event;

            texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, camWidth, camHeight);
            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            while (!done) {
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                    case SDL_QUIT:
                        done = SDL_TRUE;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym) {
                        case SDLK_w:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getTranslationMatrix(0, 0, -TRANSLATION), 
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_s:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getTranslationMatrix(0, 0, TRANSLATION),
                                cam.scene.matrix.matr44); 
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;

                        case SDLK_a:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getTranslationMatrix(TRANSLATION, 0, 0),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_d:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getTranslationMatrix(-TRANSLATION, 0, 0),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_q:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getTranslationMatrix(0, -TRANSLATION, 0),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_e:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getTranslationMatrix(0, TRANSLATION, 0),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_i:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getOXRotationMatrix(ROTATION),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_k:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getOXRotationMatrix(-ROTATION),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_j:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getOYRotationMatrix(ROTATION),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_l:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getOYRotationMatrix(-ROTATION),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_u:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getOZRotationMatrix(-ROTATION),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_o:
                            cam.scene.matrix.matr44 = cam.scene.matrix.multiplyMatrixes(cam.scene.matrix.getOZRotationMatrix(ROTATION),
                                cam.scene.matrix.matr44);
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_UP:
                            d = d + ZOOM;
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        case SDLK_DOWN:
                            if (d > ZOOM) {
                                d = d - ZOOM;
                                cam.scene.multiplyMatrixAndTriangleList();
                                cam.scene.normalizeVisableTriangleList3dPoints();
                                cam.scene.calculateAndSetVisableTriangleList();
                                cam.scene.projectVisableTriangleListTo2d(d);
                                cam.setTrianglesOnCamera();
                                cam.setTrianglesBufferCoordinates();
                                cam.paintScanLines();
                                SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                                SDL_RenderClear(renderer);
                                SDL_RenderCopy(renderer, texture, NULL, NULL);
                                SDL_RenderPresent(renderer);
                            }
                            break;
                        case SDLK_r:
                            d = 1;
                            cam.scene.matrix.matr44 = cam.scene.matrix.getUnitMatrix();
                            cam.scene.multiplyMatrixAndTriangleList();
                            cam.scene.normalizeVisableTriangleList3dPoints();
                            cam.scene.calculateAndSetVisableTriangleList();
                            cam.scene.projectVisableTriangleListTo2d(d);
                            cam.setTrianglesOnCamera();
                            cam.setTrianglesBufferCoordinates();
                            cam.paintScanLines();
                            SDL_UpdateTexture(texture, NULL, cam.buffer.data(), camWidth * 4);
                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, texture, NULL, NULL);
                            SDL_RenderPresent(renderer);
                            break;
                        }
                    }
                }
            }
            if (texture)
                SDL_DestroyTexture(texture);
            if (renderer) {
                SDL_DestroyRenderer(renderer);
            }
            if (window) {
                SDL_DestroyWindow(window);
            }
        }
        SDL_Quit();
    }
	return 0;
}
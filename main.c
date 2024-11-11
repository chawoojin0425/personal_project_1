#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

// 윈도우 초기화 및 이미지 로딩
int main(int argc, char* argv[]) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL2 초기화 실패: %s\n", SDL_GetError());
        return -1;
    }

    // SDL_image 초기화 (PNG, JPG 지원)
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        printf("SDL_image 초기화 실패: %s\n", IMG_GetError());
        SDL_Quit();
        return -1;
    }

    // 윈도우 및 렌더러 생성
    SDL_Window* window = SDL_CreateWindow("이미지 로드 예제",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("윈도우 생성 실패: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("렌더러 생성 실패: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 이미지 파일 경로
    const char* image_path_jpg = "jcshim.jpg";  // JPG 이미지
    const char* image_path_png = "jcshim.png";  // PNG 이미지

    // JPG 이미지 로드
    SDL_Texture* texture_jpg = IMG_LoadTexture(renderer, image_path_jpg);
    if (!texture_jpg) {
        printf("JPG 이미지 로드 실패: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // PNG 이미지 로드
    SDL_Texture* texture_png = IMG_LoadTexture(renderer, image_path_png);
    if (!texture_png) {
        printf("PNG 이미지 로드 실패: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture_jpg);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // 화면에 이미지를 표시
    SDL_RenderClear(renderer);
    // JPG 이미지 (왼쪽 상단에 출력)
    SDL_RenderCopy(renderer, texture_jpg, NULL, NULL);
    // PNG 이미지 (오른쪽 하단에 출력)
    SDL_Rect dstRect = { 400, 300, 400, 300 };  // PNG 이미지를 오른쪽 하단에 배치
    SDL_RenderCopy(renderer, texture_png, NULL, &dstRect);

    // 렌더링 완료
    SDL_RenderPresent(renderer);

    // 이벤트 루프
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // 자원 해제
    SDL_DestroyTexture(texture_jpg);
    SDL_DestroyTexture(texture_png);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

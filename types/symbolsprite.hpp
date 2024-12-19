#pragma once
#include <vector>
#include <array>
#include "pixel.hpp"

enum class SymbolKind {little, big, all};

namespace tetris
{
    class SymbolSprite
    {
        protected:
        std::vector<Pixel> symbolSpriteVector; 

        SymbolSprite(SymbolKind kind);

        public:
        void SetColor(const Color& c);
        void ShowSymbolSprite(SDL_Renderer* r);
        void ShowSybmolSpriteBones(SDL_Renderer* r);
        virtual void RecomputeFromStartPoint(const SDL_Point& startPoint) {}

    };

    class LittleSymbol final: public SymbolSprite
    {
        public:
        LittleSymbol(const std::array<Pixel, LITTLESYMBOLSPRITE_LENGTH>& sprite);
        void RecomputeFromStartPoint(const SDL_Point& startPoint) override;
    };
}
#include "symbolsprite.hpp"

constexpr tetris::Color SymbolBonesColor {0xfau, 0xf0u, 0xf6u, 0xff}; //Linen

namespace tetris
{
    SymbolSprite::SymbolSprite(SymbolKind kind)
    {
        switch (kind)
        {
            case SymbolKind::little:
            {
                symbolSpriteVector.reserve(LITTLESYMBOLSPRITE_LENGTH);
                break;
            }
            case SymbolKind::big:
            {
                break;
            }
            default: {}
        }
    }

    void SymbolSprite::SetColor(const Color &c)
    {
        for(auto& pixel: symbolSpriteVector)
            pixel.pColor = c;
    }

    void SymbolSprite::ShowSymbolSprite(SDL_Renderer *r)
    {
        SDL_SetRenderDrawColor(r, symbolSpriteVector[0].pColor.red,
            symbolSpriteVector[0].pColor.green, symbolSpriteVector[0].pColor.blue,
            symbolSpriteVector[0].pColor.alpha);
        for (const auto& pixel: symbolSpriteVector)
        {
            if (pixel.filled)
                SDL_RenderFillRect(r, &pixel.pixelRect);
        }
    }

    void SymbolSprite::ShowSybmolSpriteBones(SDL_Renderer *r)
    {
        SDL_SetRenderDrawColor(r, SymbolBonesColor.red, SymbolBonesColor.green,
            SymbolBonesColor.blue, SymbolBonesColor.alpha);
        for (const auto& p: symbolSpriteVector)
            SDL_RenderDrawRect(r, &p.pixelRect);
    }
    
    LittleSymbol::LittleSymbol(const std::array<Pixel, LITTLESYMBOLSPRITE_LENGTH> &sprite):
        SymbolSprite(SymbolKind::little)
    {
        for (size_t index = 0; index < sprite.size(); ++index)
        {
            symbolSpriteVector.emplace_back(sprite[index]);
        }
    }
    
    void LittleSymbol::RecomputeFromStartPoint(const SDL_Point &startPoint)
    {
        for (size_t r = 0; r < LITTLESYMBOLSPRITE_H; ++r)
        {
            for (size_t c = 0; c < LITTLESYMBOLSPRITE_W; ++c)
            {
                const size_t AT {r * LITTLESYMBOLSPRITE_W + c};
                symbolSpriteVector[AT].pixelRect.x = 
                    startPoint.x + (static_cast<int>(c) * LITTLESYMBOL_CELLSIDE);
                symbolSpriteVector[AT].pixelRect.y = 
                    startPoint.y + (static_cast<int>(r) * LITTLESYMBOL_CELLSIDE);
                symbolSpriteVector[AT].pixelRect.w = symbolSpriteVector[AT].pixelRect.h =
                    LITTLESYMBOL_CELLSIDE;
            }
        }
    }
}
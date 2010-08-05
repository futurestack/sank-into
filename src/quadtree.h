/*
 *  quadtree.h
 *  sank-into
 *
 *  Created by hornet on 8/4/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <cmath>
#include <cstddef>

#include <vector>

template <typename T>
class QuadTree
    {
    public:
        static const size_t SIZE_1x1 =      0;
        static const size_t SIZE_2x2 =      1;
        static const size_t SIZE_4x4 =      2;
        static const size_t SIZE_8x8 =      3;
        static const size_t SIZE_16x16 =    4;
        static const size_t SIZE_32x32 =    5;
        static const size_t SIZE_64x64 =    6;
        static const size_t SIZE_128x128 =  7;
        static const size_t SIZE_256x256 =  8;
        static const size_t SIZE_512x512 =  9;
        static const size_t SIZE_1024x1024 =10;
        
        enum Sector
        {
            TOP_LEFT, TOP_RIGHT, BOT_LEFT, BOT_RIGHT
        };
        
        /// Constructs a quadtree with a width and height of 2^layers.
        QuadTree(size_t layers);
        virtual ~QuadTree();
        
        virtual size_t getWidth() const;
        virtual size_t getHeight() const;
        
        /// Sets an object for this tree.
        virtual void setObject(T data);
        /// Gets the object for this tree.
        virtual T &getObject();
        
        /// Sets the object or every sub quadtree with this object if not
        /// at base.
        virtual void setObjects(T data);
        
        /// Returns a list of all the objects in the quadtree.
        virtual void getObjects(std::vector<T> &vec) const;
        
        /// Returns a sub-quadtree of this tree, where l is the layer of the tree
        /// to index. Layer of 0 gives you a 1x1 tree, which can only be index
        /// by 0,0. Layer of 1 gives you a 2x2 vision of this tree.
        virtual QuadTree<T> &getQuadTree(size_t l, size_t x, size_t y);
        
        // Functions for layering.
        virtual size_t getLayers() const;
        
        /// Gets the element at the x,y position.
        virtual T &operator ()(size_t x, size_t y);
        /// Gets one of the four sub quadtrees.
        virtual QuadTree<T> &operator ()(Sector sec);
    protected:
        QuadTree<T> *m_topLeft;
        QuadTree<T> *m_topRight;
        QuadTree<T> *m_botRight;
        QuadTree<T> *m_botLeft;
        T m_data;
        size_t m_layers;
        size_t m_curLayer;
    };

template <typename T>
QuadTree<T>::QuadTree(size_t layers)
{
    m_layers = layers;
    m_curLayer = layers;
    
    if (m_layers > 0)
    {
        m_topLeft = new QuadTree<T>(m_layers - 1);
        m_topRight = new QuadTree<T>(m_layers - 1);
        m_botLeft = new QuadTree<T>(m_layers - 1);
        m_botRight = new QuadTree<T>(m_layers - 1);
    }
    else
    {
        m_topLeft = NULL;
        m_topRight = NULL;
        m_botLeft = NULL;
        m_botRight = NULL;
    }
}

template <typename T>
QuadTree<T>::~QuadTree()
{
    if (m_topLeft && m_topRight && m_botLeft && m_botRight)
    {
        delete m_topLeft;
        delete m_topRight;
        delete m_botLeft;
        delete m_botRight;
    }
}

template <typename T>
size_t QuadTree<T>::getWidth() const
{
    return static_cast<size_t>(pow(2.0f, (float)m_layers));
}

template <typename T>
size_t QuadTree<T>::getHeight() const
{
    return static_cast<size_t>(pow(2.0f, (float)m_layers));
}

template <typename T>
void QuadTree<T>::setObject(T data)
{
    m_data = data;
}

template <typename T>
T &QuadTree<T>::getObject()
{
    return m_data;
}

template <typename T>
void QuadTree<T>::setObjects(T data)
{
    if (m_topLeft && m_topRight && m_botLeft && m_botRight)
    {
        m_topLeft->setObjects(data);
        m_topRight->setObjects(data);
        m_botLeft->setObjects(data);
        m_botRight->setObjects(data);
        m_data = data;
    }
    else
    {
        m_data = data;
    }
}

template <typename T>
void QuadTree<T>::getObjects(std::vector<T> &vec) const
{
    if (m_topLeft && m_topRight && m_botLeft && m_botRight)
    {
        m_topLeft->getObjects(vec);
        m_topRight->getObjects(vec);
        m_botLeft->getObjects(vec);
        m_botRight->getObjects(vec);
    }
    else
    {
        vec.push_back(m_data);
    }
}

template <typename T>
QuadTree<T> &QuadTree<T>::getQuadTree(size_t d, size_t x, size_t y)
{
    size_t width = static_cast<size_t>(pow(2.0f, (float)d));
    size_t height = static_cast<size_t>(pow(2.0f, (float)d));
    
    if (d > 0)
    {
        if (x < width / 2 && y < height / 2)
        {
            return m_topLeft->getQuadTree(d - 1, x, y);
        }
        else if (x < width && y < height / 2)
        {
            return m_topRight->getQuadTree(d - 1, x - width / 2, y);
        }
        else if (x < width / 2 && y < height)
        {
            return m_botLeft->getQuadTree(d - 1, x, y - height / 2);
        }
        else
        {
            return m_botRight->getQuadTree(d - 1, x - width / 2, y - height / 2);
        }
    }
    else
    {
        return (*this);
    }
}

template <typename T>
size_t QuadTree<T>::getLayers() const
{
    return m_layers;
}

template <typename T>
T &QuadTree<T>::operator ()(size_t x, size_t y)
{
    return getQuadTree(m_layers, x, y).getObject();
}

template <typename T>
QuadTree<T> &QuadTree<T>::operator ()(Sector sec)
{
    switch (sec)
    {
        case TOP_LEFT:
            return (*m_topLeft);
        case TOP_RIGHT:
            return (*m_topRight);
        case BOT_LEFT:
            return (*m_botLeft);
        case BOT_RIGHT:
            return (*m_botRight);
    }
}

#endif /* QUADTREE_H_ */


#include <SDL/SDL.h>
#include <iostream>

using std::cout;
using std::endl;

const int WIDTH = 640;
const int HEIGHT = 480;

class BlockWorld : public QuadTree<bool>
{
public:
    BlockWorld() :
    QuadTree<bool>(QuadTree<bool>::SIZE_32x32)
    {
    }
    virtual ~BlockWorld() { }
    
    virtual void Draw()
    {
        Draw(*this, 0, 0, WIDTH, HEIGHT);
    }
    
    virtual void Update()
    {
        
    }
    
    virtual void Click(int x, int y)
    {
        int layerWidth = pow(2, getLayers());
        int layerHeight = pow(2, getLayers());
        int blockx = x / (WIDTH / layerWidth);
        int blocky = y / (HEIGHT / layerHeight);
        (*this)(blockx, blocky) = true;
    }
    
    virtual void Key(unsigned int num, int x, int y)
    {
        if (num > getLayers())
            return;
        int layerWidth = pow(2, num);
        int layerHeight = pow(2, num);
        int blockx = x / (WIDTH / layerWidth);
        int blocky = y / (HEIGHT / layerHeight);
        getQuadTree(num, blockx, blocky).setObjects(false);
        getQuadTree(num, blockx, blocky).setObject(true);
    }
    
    virtual void BreakUp(int x, int y)
    {
        unsigned int layers = 1;
        int blockx = x, blocky = y;
        
        while (layers < getLayers())
        {
            int layerWidth = pow(2, layers);
            int layerHeight = pow(2, layers);
            blockx = x / (WIDTH / layerWidth);
            blocky = y / (HEIGHT / layerHeight);
            
            if (getQuadTree(layers, blockx, blocky).getObject() == true)
            {
                getQuadTree(layers, blockx, blocky).setObjects(false);
                getQuadTree(layers, blockx, blocky)(TOP_LEFT).setObject(true);
                getQuadTree(layers, blockx, blocky)(TOP_RIGHT).setObject(true);
                getQuadTree(layers, blockx, blocky)(BOT_LEFT).setObject(true);
                getQuadTree(layers, blockx, blocky)(BOT_RIGHT).setObject(true);
                return;
            }
            else
            {
                layers += 1;
            }
        }
    }
protected:
    
    virtual void Draw(QuadTree<bool> &bw, int x, int y, int w, int h)
    {
        if (bw.getObject() == false)
        {
            if (bw.getLayers() == 0)
                return;
            Draw(bw(TOP_LEFT),  x,         y,         w / 2, h / 2);
            Draw(bw(TOP_RIGHT), x + w / 2, y,         w / 2, h / 2);
            Draw(bw(BOT_LEFT),  x,         y + h / 2, w / 2, h / 2);
            Draw(bw(BOT_RIGHT), x + w / 2, y + h / 2, w / 2, h / 2);
        }
        else
        {
            SDL_Rect r;
            r.x = x + 1;
            r.y = y + 1;
            r.w = w - 1;
            r.h = h - 1;
            SDL_FillRect(SDL_GetVideoSurface(), &r, 0x00CCAA77);
        }
    }
};

/*
int main()
{
    bool running = true;
    SDL_Event ev;
    BlockWorld bw;
    
    SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_DOUBLEBUF);
    
    while (running)
    {
        SDL_FillRect(SDL_GetVideoSurface(), NULL, 0);
        bw.Draw();
        bw.Update();
        SDL_Flip(SDL_GetVideoSurface());
        
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    bw.Click(ev.motion.x, ev.motion.y);
                    break;
                case SDL_KEYDOWN:
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (ev.key.keysym.sym == SDLK_c)
                        bw.setObjects(false);
                    if (ev.key.keysym.sym == SDLK_s)
                        bw.BreakUp(x, y);
                    else
                        bw.Key(ev.key.keysym.sym - '0', x, y);
                    break;
                }
                default:
                    break;
            }
        }
    }
    
    SDL_Quit();
    return 0;
}

*/
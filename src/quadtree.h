///
/// Quad tree implementation.
///
#ifndef QUADTREE_H
#define QUADTREE_H

#include <cmath>
#include <cstddef>

template <typename T>
class QuadTree
    {
    public:
        // Helper constants.
        enum
        {
            SIZE_1x1 =     0, SIZE_2x2 =        1, SIZE_4x4 =       2,
            SIZE_8x8 =     3, SIZE_16x16 =      4, SIZE_32x32 =     5,
            SIZE_64x64 =   6, SIZE_128x128 =    7, SIZE_256x256 =   8,
            SIZE_512x512 = 9, SIZE_1024x1024 = 10, SIZE_2048x2048 = 11
        };
        
        /// Constructs a quadtree with a width and height of 2^layers.
        QuadTree(size_t layers=0);
        virtual ~QuadTree();
        
        /// Gets the number of layers this tree has.
        virtual size_t layers() const { return m_layers; }
        
        /// Gets the width of the "current layer". See the operator []
        /// for details.
        virtual size_t width() const;
        
        /// Gets the height of the "current layer". See the operator []
        /// for details.
        virtual size_t height() const;
        
        /// Returns true if this tree has a parent. A parent always
        /// has four children.
        virtual bool hasParent() const { return m_parent != NULL; }
        
        /// Returns the parent. Segfaults if this tree doesn't have one. :(
        virtual QuadTree<T> &parent() { return *m_parent; }
        
        /// Sets this tree's object, and EVERY child's object to this.
        virtual void setAllObjects(T to);
        
        /// Returns a reference the templated object.
        virtual T &object() { return m_data; }
        
        /// Returns the tree at the X and Y position on the "current layer". See
        /// the operator [] for details.
        virtual QuadTree<T> &operator ()(size_t x, size_t y);
        
        
        
        /// Sets the current layer to index from. Useful for getting any element
        /// you desire in the whole tree.
        ///
        /// This operator effects the quad tree class in the following ways:
        /// * width() and height() function returns the width and height
        ///   (respectively) of the current layer. For example:
        ///   `tree[0].width()` will return 1 ALWAYS :P
        /// * The () operator indexes at that current layer. For example:
        ///   `tree[0](0, 0)` will return just `tree` and
        ///   `tree[1](<0 or 1>, <0 or 1).parent()` will return just `tree`
        ///
        /// Note: It's a VERY good idea to ALWAYS use this before calling
        ///       width(), height and () so you know for sure you're where
        ///       you want to be.
        virtual QuadTree<T> &operator [](int layer);
        
        
        
    protected:
        // It's a friggin forest.
        QuadTree<T> *m_parent;
        QuadTree<T> *m_topLeft;
        QuadTree<T> *m_topRight;
        QuadTree<T> *m_botRight;
        QuadTree<T> *m_botLeft;
        
        // The dada. Eh-hem, I mean data.
        T m_data;
        
        // The number of layers indexable.
        size_t m_layers;
        // The current layer we're indexing.
        size_t m_curLayer;
        
        // Do we have the right to free them? :O
        bool m_owner;
        
    private:
        // Private function to set parents n' stuff.
        QuadTree(QuadTree<T> *parent, size_t layers);
        
        // Copying *Soon to come*
        QuadTree(const QuadTree<T> &qt);
        QuadTree<T> &operator =(const QuadTree<T> &qt);
    };

template <typename T>
QuadTree<T>::QuadTree(size_t layers)
{
    m_layers = layers;
    m_curLayer = layers;
    // An orphan. :'(
    m_parent = NULL;
    
    m_owner = true;
    
    if (m_layers > 0)
    {
        // Use the private constructor so we can supply a parent.
        m_topLeft = new QuadTree<T>(this, m_layers - 1);
        m_topRight = new QuadTree<T>(this, m_layers - 1);
        m_botLeft = new QuadTree<T>(this, m_layers - 1);
        m_botRight = new QuadTree<T>(this, m_layers - 1);
    }
    else
    {
        m_topLeft = NULL;
        m_topRight = NULL;
        m_botLeft = NULL;
        m_botRight = NULL;
    }
}

// PRIVATE, GO AWAY
template <typename T>
QuadTree<T>::QuadTree(const QuadTree<T> &qt)
{
    *this = qt;
}

template <typename T>
QuadTree<T>::QuadTree(QuadTree<T> *parent, size_t layers)
{
    m_layers = layers;
    m_curLayer = layers;
    // Yay!
    m_parent = parent;
    
    m_owner = true;
    
    if (m_layers > 0)
    {
        // printf("slow\n");                                       jk
        m_topLeft = new QuadTree<T>(this, m_layers - 1);
        m_topRight = new QuadTree<T>(this, m_layers - 1);
        m_botLeft = new QuadTree<T>(this, m_layers - 1);
        m_botRight = new QuadTree<T>(this, m_layers - 1);
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
    if (m_layers > 0 && m_owner)
    {
        delete m_topLeft;
        delete m_topRight;
        delete m_botLeft;
        delete m_botRight;
    }
}

template <typename T>
size_t QuadTree<T>::width() const
{
    return static_cast<size_t>(pow(2.0f, (float)m_curLayer));
}

template <typename T>
size_t QuadTree<T>::height() const
{
    return static_cast<size_t>(pow(2.0f, (float)m_curLayer));
}

template <typename T>
void QuadTree<T>::setAllObjects(T to)
{
    this->object() = to;
    
    // Children?
    if (m_layers > 0)
    {
        m_topLeft->setAllObjects(to);
        m_topRight->setAllObjects(to);
        m_botLeft->setAllObjects(to);
        m_botRight->setAllObjects(to);
    }
}

template <typename T>
QuadTree<T> &QuadTree<T>::operator ()(size_t x, size_t y)
{
    size_t d = m_curLayer;
    
    QuadTree<T> *ptr = this;
    
    // Might be possible to implement this recursively. Where might means
    // definitely.
    while (d > 0)
    {
        size_t width = static_cast<size_t>(pow(2.0f, (float)d));
        size_t height = static_cast<size_t>(pow(2.0f, (float)d));
        
        if (x < width / 2 && y < height / 2)
        {
            ptr = ptr->m_topLeft;
        }
        else if (x < width && y < height / 2)
        {
            x -= width / 2;
            ptr = ptr->m_topRight;
        }
        else if (x < width / 2 && y < height)
        {
            y -= height / 2;
            ptr = ptr->m_botLeft;
        }
        else
        {
            x -= width / 2;
            y -= height / 2;
            ptr = ptr->m_botRight;
        }
        
        d -= 1;
    }
    
    // Segfault? :D
    return *ptr;
}

template <typename T>
QuadTree<T> &QuadTree<T>::operator [](int layer)
{
    // Python indexing.
    if (layer < 0)
        m_curLayer = m_layers + (layer + 1);
    else
        m_curLayer = layer;
    return *this;
}

// PRIVATE, GO AWAY
template <typename T>
QuadTree<T> &QuadTree<T>::operator =(const QuadTree<T> &qt)
{
    if (this != &qt)
    {
        m_layers = qt.m_layers;
        m_curLayer = qt.m_curLayer;
        m_parent = qt.m_parent;
        m_owner = false;
        m_data = qt.m_data;
        
        if (m_layers != 0)
        {
            m_topLeft = qt.m_topLeft;
            m_topRight = qt.m_topRight;
            m_botLeft = qt.m_botLeft;
            m_botRight = qt.m_botRight;
        }
        else
        {
            m_topLeft = NULL;
            m_topRight = NULL;
            m_botLeft = NULL;
            m_botRight = NULL;
        }
    }
    return *this;
}

#endif 
/* QUADTREE_H */


/*
 
#include <cassert>
#include <SDL/SDL.h>

#if 1
const int WIDTH = 640;
const int HEIGHT = 480;

class gameMap : public QuadTree<bool>
{
public:
    gameMap() :
    QuadTree<bool>(QuadTree<bool>::SIZE_32x32)
    {
    }
    virtual ~gameMap() { }
    
    virtual void Draw()
    {
        Draw(*this, 0, 0, WIDTH, HEIGHT);
    }
    
    virtual void Update()
    {
        
    }
    
    virtual void Click(int x, int y)
    {
        int blockx = x / (WIDTH / (*this)[-1].width());
        int blocky = y / (HEIGHT / (*this)[-1].width());
        (*this)[-1](blockx, blocky).object() = true;
    }
    
    virtual void Key(unsigned int num, int x, int y)
    {
        if (num > layers())
            return;
        int blockx = x / (WIDTH / (*this)[num].width());
        int blocky = y / (HEIGHT / (*this)[num].width());
        (*this)[num](blockx, blocky).object() = true;
    }
    
    virtual void BreakUp(int x, int y)
    {
        int blockx = x / (WIDTH / (*this)[-1].width());
        int blocky = y / (HEIGHT / (*this)[-1].width());
        
        QuadTree<bool> *qt = &(*this)[-1](blockx, blocky);
        
        while (true)
        {
            if (qt->object() == true && qt->layers() > 0)
            {
                qt->setAllObjects(false);
                (*qt)[1](0, 0).object() = true;
                (*qt)[1](0, 1).object() = true;
                (*qt)[1](1, 0).object() = true;
                (*qt)[1](1, 1).object() = true;
                return;
            }
            if (qt->hasParent())
                qt = &qt->parent();
            else
                break;
        }
    }
protected:
    
    virtual void Draw(QuadTree<bool> &bw, int x, int y, int w, int h)
    {
        if (bw.object() == false)
        {
            if (bw.layers() == 0)
                return;
            Draw(bw[1](0, 0),  x,         y,         w / 2, h / 2);
            Draw(bw[1](1, 0), x + w / 2, y,         w / 2, h / 2);
            Draw(bw[1](0, 1),  x,         y + h / 2, w / 2, h / 2);
            Draw(bw[1](1, 1), x + w / 2, y + h / 2, w / 2, h / 2);
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

int main()
{
    bool running = true;
    SDL_Event ev;
    gameMap bw;
    bw.setAllObjects(false);
    
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
                        bw.setAllObjects(false);
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
#endif

*/
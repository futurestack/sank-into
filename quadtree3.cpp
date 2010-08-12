///
/// Quad tree implementation.
///
#ifndef QUADTREE_H
#define QUADTREE_H

#include <cmath>
#include <cstddef>

#include <vector>

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
    QuadTree(size_t layers);
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
    
private:
    // Private function to set parents n' stuff.
    QuadTree(QuadTree<T> *parent, size_t layers);
};

template <typename T>
QuadTree<T>::QuadTree(size_t layers)
{
    m_layers = layers;
    m_curLayer = layers;
    // An orphan. :'(
    m_parent = NULL;
    
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

template <typename T>
QuadTree<T>::QuadTree(QuadTree<T> *parent, size_t layers)
{
    m_layers = layers;
    m_curLayer = layers;
    // Yay!
    m_parent = parent;
    
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
    if (m_topLeft && m_topRight && m_botLeft && m_botRight)
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
QuadTree<T> &QuadTree<T>::operator ()(size_t x, size_t y)
{
    size_t d = 0;
    
    QuadTree<T> *ptr = this;
    
    // Might be possible to implement this recursively. Where might means
    // definitely.
    while (d < m_curLayer)
    {
        size_t width = static_cast<size_t>(pow(2.0f, (float)d + 1));
        size_t height = static_cast<size_t>(pow(2.0f, (float)d + 1));
        
        if (x < width / 2 && y < height / 2)
        {
            ptr = ptr->m_topLeft;
        }
        else if (x < width && y < height / 2)
        {
            ptr = ptr->m_topRight;
        }
        else if (x < width / 2 && y < height)
        {
            ptr = ptr->m_botLeft;
        }
        else
        {
            ptr = ptr->m_botRight;
        }
        d++;
    }
    
    // Segfault? :D
    return *ptr;
}

template <typename T>
QuadTree<T> &QuadTree<T>::operator [](int layer)
{
    // Python indexing.
    if (layer < 0)
        layer = m_layers + (layer + 1);
    else
        m_curLayer = layer;
    return *this;
}

#endif /* QUADTREE_H */
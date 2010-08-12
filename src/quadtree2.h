/*
 *  quadtree2.h
 *  sank-into
 *
 *  Created by hornet on 8/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef QUADTREE2_H_
#define QUADTREE2_H_

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
        
        /// Constructs a quadtree with a width and height of 2^layers.
        QuadTree(size_t layers);
        virtual ~QuadTree();
        
        virtual size_t layers() const { return m_layers; }
        virtual size_t width() const;
        virtual size_t height() const;
        virtual bool hasParent() const { return m_parent != NULL; }
        virtual QuadTree<T> &parent() { return *m_parent; }
        virtual T &object() { return m_data; }
        
        virtual QuadTree<T> &operator ()(size_t x, size_t y);
        virtual QuadTree<T> &operator [](int layer);
    protected:
        QuadTree<T> *m_parent;
        QuadTree<T> *m_topLeft;
        QuadTree<T> *m_topRight;
        QuadTree<T> *m_botRight;
        QuadTree<T> *m_botLeft;
        T m_data;
        size_t m_layers;
        size_t m_curLayer;
        
    private:
        QuadTree(QuadTree<T> *parent, size_t layers);
    };

template <typename T>
QuadTree<T>::QuadTree(size_t layers)
{
    m_layers = layers;
    m_curLayer = layers;
    m_parent = NULL;
    
    if (m_layers > 0)
    {
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
    m_parent = parent;
    
    if (m_layers > 0)
    {
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
    
    return *ptr;
}

template <typename T>
QuadTree<T> &QuadTree<T>::operator [](int layer)
{
    if (layer < 0)
        layer = m_layers + (layer + 1);
    else
        m_curLayer = layer;
    return *this;
}

#endif /* QUADTREE_H_ */

#include <iostream>

using std::cout;
using std::endl;

int main()
{
    // Constructs a quad tree with 2 layers that looks like:
    // Layer 0 (1x1)
    //  --
    // |  |
    //  --
    // Layer 1 (2x2)
    //  -- --
    // |  |  |
    //  -- --
    // |  |  |
    //  -- --
    QuadTree<int> tree(1);
    
    // Default layer that we're indexing is 1 (2x2)
    cout << tree.width() << " " << tree.height() << endl;
    
    // Explicitely state the layer to index with [], it's
    // a VERY good idea to always do this.
    
    // NOTE: Setting the current layer index will only effect width(),
    // height() and the operator () calls.
    // NOTE: Use [-1] to get the last layer, [-2] to get the second to last.
    
    // Setting XX to 10, ?? are undefined (default constructed)
    //  -- --
    // |XX|??|
    //  -- --
    // |??|??|
    //  -- --
    tree[tree.layers()](0, 0).object() = 10;
    tree[-1](0, 0).object() = 10; // Same thing as above.
    // Setting XX to 5
    //  --
    // |XX|
    //  --
    tree[0](0, 0).object() = 5;
    // Printing 10
    //  -- --
    // |10|??|
    //  -- --
    // |??|??|
    //  -- --
    cout << tree[1](0, 0).object() << endl;
    
    // Nifty, eh?
    tree[-1](1, 1).parent().object() -= 500;
    cout << tree.object() << endl; // Prints -495
    
    return 0;
}

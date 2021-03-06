#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

template <typename T>
class HuffmanNode 
{
protected:
	int _weight;
public:

	//gets weight of huffman node and children
	virtual int getWeight()
	{
		return _weight;
	}

		// increment the weight
	void setWeight (void)
	{
		_weight++;
	}

	//determines if node is a leaf or not
	virtual bool isLeaf() = 0;
};

#endif

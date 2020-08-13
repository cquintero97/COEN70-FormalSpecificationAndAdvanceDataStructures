namespace scu_coen70_lab_9
{
	
    template <class Process, class BTNode>
    void inorder(Process f, BTNode* node_ptr)
    {
        if (node_ptr != NULL)
        {
            inorder(f, node_ptr->left());
            f(node_ptr->data());
            inorder(f, node_ptr->right());
        }
    }
    
    template <class Process, class BTNode>
    void postorder(Process f, BTNode* node_ptr)
    {
        if (node_ptr != NULL)
        {
            postorder(f, node_ptr->left());
            postorder(f, node_ptr->right());
            f(node_ptr->data());
        }
    }
    
    template <class Process, class BTNode>
    void preorder(Process f, BTNode* node_ptr)
    {
        if (node_ptr != NULL)
        {
            f(node_ptr->data());
            preorder(f, node_ptr->left());
            preorder(f, node_ptr->right());
        }
    }
    
    template <class Item, class SizeType>
    void print(binary_tree_node<Item>* node_ptr, SizeType depth)
    {
        if (node_ptr != NULL)
        {
            print(node_ptr->right(), depth+1);
            std::cout << std::setw(4*depth) << "";
            std::cout << node_ptr->data() << std::endl;
            print(node_ptr->left(), depth+1);
        }
    }
    
    template <class Item>
    void tree_clear(binary_tree_node<Item>*& root_ptr)
    {
        binary_tree_node<Item>* child;
        if (root_ptr != NULL)
        {
            child = root_ptr->left();
            tree_clear(child);
            child = root_ptr->right();
            tree_clear(child);
            delete root_ptr;
            root_ptr = NULL;
        }
    }
    
    template <class Item>
    binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr)
    {
        binary_tree_node<Item> *l_ptr;
        binary_tree_node<Item> *r_ptr;
        if (root_ptr == NULL)
		{
            return NULL;
		}
        else
        {
            l_ptr = tree_copy(root_ptr->left());
            r_ptr = tree_copy(root_ptr->right());
            return
            new binary_tree_node<Item>(root_ptr->data(), l_ptr, r_ptr);
        }
    }
    
    template <class Item>
    size_t tree_size(const binary_tree_node<Item>* node_ptr)
    {
        if (node_ptr == NULL)
            return 0;
        else
            return
            1 + tree_size(node_ptr->left()) + tree_size(node_ptr->right());
    }
}

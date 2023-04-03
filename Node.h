class Node{
public:
    Node(int puzzle[MAXN][MAXN]);//constructor
    void heuristic(int puzzle_end[MAXN][MAXN]);//heuristic function
    void get_hash_value();
    int puzzle[MAXN][MAXN];
    int fval;//total weight
    int gval;//distance
    int hval;//heuristic function value
    int hash_value;//hash value
};

Node::Node(int puzzle[MAXN][MAXN])
{
    this->gval=0;
    for(int i=0;i<MAXN;i++)
    {
        for(int j=0;j<MAXN;j++)
        {
            this->puzzle[i][j]=puzzle[i][j];
        }
    }
}

void Node::get_hash_value()
{
    hash_value=0;
    for(int i=0;i<MAXN;i++)
    {
        for(int j=0;j<MAXN;j++)
        {
            hash_value+=pow(10,(i*MAXN+j))*puzzle[i][j];
        }
    }
}

void Node::heuristic(int puzzle_end[MAXN][MAXN])//how many blocks are not on position 
{
    this->hval=0;
    for(int i=0;i<MAXN;i++)
    {
        for(int j=0;j<MAXN;j++)
        {
            if(puzzle[i][j]!=puzzle_end[i][j])
            {
                hval++;
            }
        }
    }
    this->fval=hval+gval;
}

struct cmp//compare function
{
    bool operator()(Node &a,Node &b)
    {
        return a.fval>b.fval;
    }
};

void generate(bool *visited,int *parent,priority_queue<Node,vector<Node>,cmp>& open,int &generate,Node& nd,int puzzle_end[MAXN][MAXN])
{//generate next nodes
    for(int i=0;i<MAXN;i++)
    {
        for(int j=0;j<MAXN;j++)
        {
            if(nd.puzzle[i][j]==0)
            {
                if(i-1>=0)//up
                {
                    Node next_u(nd.puzzle);
                    next_u.puzzle[i][j]=next_u.puzzle[i-1][j];
                    next_u.puzzle[i-1][j]=0;
                    next_u.gval=nd.gval+1;
                    next_u.heuristic(puzzle_end);
                    next_u.get_hash_value();
                    if(!visited[next_u.hash_value])
                    {
                        parent[next_u.hash_value]=nd.hash_value;
                        generate++;
                        open.push(next_u);
                    }    
                }
                if(i+1<MAXN)//down
                {
                    Node next_d(nd.puzzle);
                    next_d.puzzle[i][j]=next_d.puzzle[i+1][j];
                    next_d.puzzle[i+1][j]=0;
                    next_d.gval=nd.gval+1;
                    next_d.heuristic(puzzle_end);
                    next_d.get_hash_value();
                    if(!visited[next_d.hash_value])
                    {
                        parent[next_d.hash_value]=nd.hash_value;
                        generate++;
                        open.push(next_d);
                    }    
                }
                if(j-1>=0)//left
                {
                    Node next_l(nd.puzzle);
                    next_l.puzzle[i][j]=next_l.puzzle[i][j-1];
                    next_l.puzzle[i][j-1]=0;
                    next_l.gval=nd.gval+1;
                    next_l.heuristic(puzzle_end);
                    next_l.get_hash_value();
                    if(!visited[next_l.hash_value])
                    {
                        parent[next_l.hash_value]=nd.hash_value;
                        generate++;
                        open.push(next_l);
                    }  
                }
                if(j+1<MAXN)//right
                {
                    Node next_r(nd.puzzle);
                    next_r.puzzle[i][j]=next_r.puzzle[i][j+1];
                    next_r.puzzle[i][j+1]=0;
                    next_r.gval=nd.gval+1;
                    next_r.heuristic(puzzle_end);
                    next_r.get_hash_value();
                    if(!visited[next_r.hash_value])
                    {
                        parent[next_r.hash_value]=nd.hash_value;
                        generate++;
                        open.push(next_r);
                    }  
                }
                return;
            }
        }
    }
}
class puzzle{
public:
    puzzle();//constructor
    int puzzle_now[MAXN][MAXN];
    void Astar();
};

puzzle::puzzle()
{
    for(int i=0;i<MAXN;i++)
    {
        for(int j=0;j<MAXN;j++)
        {
            cin>>this->puzzle_now[i][j];
        }
    }
}

void puzzle::Astar()
{
    priority_queue<Node,vector<Node>,cmp> open;
    bool *visited=new bool[1000000000]();//record the node has been visited
    int *parent=new int[1000000000]();//record the parent node 
    int puzzle_end[MAXN][MAXN];
    for(int i=0;i<MAXN;i++)
    {
        for(int j=0;j<MAXN;j++)
        {
            cin>>puzzle_end[i][j];
        }
    }
    Node begin(puzzle_now);
    begin.heuristic(puzzle_end);
    begin.get_hash_value();
    Node end(puzzle_end);
    end.get_hash_value();
    open.push(begin);
    int search_node=0;
    int generate_node=0;
    clock_t start_time=clock();
    while(!open.empty())
    {
        if(!visited[open.top().hash_value])
        {
            Node now(open.top());
            open.pop();
            search_node++;
            if(now.hash_value==end.hash_value)
            {
                cout<<"Complete!"<<endl;
                cout<<"Step: "<<now.gval<<endl;
                break;
            }
            else
            {
                visited[now.hash_value]=true;
                generate(visited,parent,open,generate_node,now,puzzle_end);
            }
        }
        else
        {
            open.pop();
        }
    }
    if(open.empty())
    {
        cout<<"No solution!"<<endl;
    }
    clock_t stop_time=clock();
    cout<<"Search Nodes: "<<search_node<<endl;
    cout<<"Generate Nodes: "<<generate_node<<endl;
    cout<<"Time:"<<((double)(stop_time-start_time)/CLOCKS_PER_SEC)*1000<<" ms"<<endl;
    cout<<"Now begin trace:"<<endl;
    int node_trace=end.hash_value;
    int n=0;
    stack<string> help;//use stack to help trace back
    do
    {
        string thispuzzle=to_string(node_trace);
        reverse(thispuzzle.begin(),thispuzzle.end());
        if(thispuzzle.size()<MAXN*MAXN)//add '0' that might lose when record
        {
            thispuzzle.push_back('0');
        }
        help.push(thispuzzle);
        node_trace=parent[node_trace];
    }while(parent[node_trace]!=node_trace);
    while(!help.empty())
    {
        cout<<"Step "<<n<<":"<<endl;
        string::iterator it=help.top().begin();
        for(int i=0;i<MAXN;i++)
        {
            for(int j=0;j<MAXN;j++)
            {
                cout<<(*it)<<" ";
                it++;
            }
            cout<<endl;
        }
        help.pop();
        n++;
    }
}
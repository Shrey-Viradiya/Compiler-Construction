int GraphColorImplementation(){
    int vertices, choice;
    bool** graph = NULL;
    struct Graph* GRP = NULL;

    printf("Graph Coloring Problem....");
    printf("Enter the number of vertices: \n");
    scanf("%d",&vertices);

    printf("Choose the approach\n1: add adjacency matrix of the graph\n2: add the edges of the graph\n");
    scanf("%d", &choice);


    switch (choice){
        case 1:
            graph = (bool **) calloc(vertices, sizeof(bool *));
            for (int k = 0; k < vertices; ++k) {
                graph[k] = (bool *) calloc(vertices, sizeof(bool));
            }

            printf("\n\nEnter the adjacency matrix of the graph\n");
            printf("________________________________________\n");

            for (int i = 0; i < vertices; ++i) {
                for (int j = 0; j < vertices; ++j) {
                    scanf("%d", &graph[i][j]);
                }
            }
            break;

        case 2:
            graph = (bool **) calloc(vertices, sizeof(bool *));
            for (int k = 0; k < vertices; ++k) {
                graph[k] = (bool *) calloc(vertices, sizeof(bool));
            }

            GRP = createGraph(vertices, graph);

            printf("n Vertices are labeled as 0, 1, to n-1: ");
            printf("\nInstructions: ");
            printf("\nTo add an edge, enter two vertices \"i j\" space separated");
            printf("\nIf any of the i or j is greater or equal to no of vertices");
            printf("\nthan input is rejected and asked for one more input");
            printf("\n\nChoose options\n1: add edge\n0: exit\n");

            int choice2;

            do{
                printf("\nChoice: \n");
                scanf("%d", &choice2);

                if (choice2 == 1){
                    int src,des;
                    printf("\n");
                    scanf("%d %d",&src, &des);

                    if (src >= vertices || des >= vertices){
                        printf("Invalid Input");
                        continue;
                    }

                    addEdge(GRP,src,des,graph);
                    
                    graph[src][des] = 1;
                    graph[des][src] = 1;
                    printf("\nEdge Added\n");

                }
            }while(choice2 != 0);

            printGraph(GRP);
            break;
        default:
            printf("Not Sure What to Do! Please try again...");
            break;
    }

    int m = 1;
    int *solution = NULL;

    while (true) {
        solution = SolveGraph(graph, m, vertices);
        if (solution != NULL) {
            break;
        }
        ++m;
    }

    printf("Minimum Number of Different colors \nrequired to Color the graph: %d",m);
    printSolution(solution, vertices);

    return 0;
}
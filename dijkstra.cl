/**
 * This is the simple kernel. For the current work item,
 * which can be addressed using the value returned by
 * get_global_id(0), copy the contents from src to dest.
 */
#define I 998

__kernel void dijkstraKernel1(
		__global int *distance,
		__global int *updateDistance,
		__global int *preced,
		__global int *visited,
		__global int *nodes,
		__global int *edges,
		__global int *weights,
		int countNodes,
		int countEdges,
		__global int *lastEdge
		)
{
	
	int t = get_global_id(0);
	int old, i;
	if (visited[t] == 0) {
		visited[t] = 1;
		
		
		int begin = nodes[t];
		int end;
		if(t + 1 < (countNodes)) {
			end = nodes[t + 1];
		} else {
			end = countEdges;
		}
		
		int edge;
		for (i = begin; i < end; i++) {
			edge = edges[i];
			
			old = distance[t] + weights[i];
			if(old < updateDistance[edge]) {
				updateDistance[edge] = old;
				*lastEdge = t;
				preced[edge] = t;
			}
			
		}
	}

}

__kernel void dijkstraKernel2(
		__global int *distance,
		__global int *updateDistance,
		__global int *predec,
		__global int *visited,
		__global int *lastEdge
		)
{
	int t = get_global_id(0);

	if (distance[t] > updateDistance[t]) {	
		distance[t] = updateDistance[t];
		predec[t] = *lastEdge;
		visited[t] = 0;
	}

	updateDistance[t] = distance[t];

}


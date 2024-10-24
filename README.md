We will implement a feed-forward neural network that will run on multiple machines using MPI. 
The network will include ReLU, back-propagation, dropout, softmax, and cross-entropy loss using the C++ programming language.

The system will work as follows: 
1) Each processor will receive different batches of the training dataset and forward its inputs to produce outputs, after which the loss for each sample is computed.
3) Using the MPI AllGather function, the total loss for the current epoch is aggregated.
4) The weights are then updated via backpropagation.
5) Hence, we will be implementing the derivative of each layer mentioned earlier. 

We will test our implementation with a simple binary classification task, using the airplane satisfaction dataset in the link below:

https://www.kaggle.com/datasets/mysarahmadbhat/airline-passenger-satisfaction

We expect to be able to utilize low-powered machines to train a neural network using distributed and parallel processing techniques. 
We expect our approach to scale well across multiple CPU cores and multiple networked machines since the individual components of the neural network are parallelizable (e.g. the regularization function ReLU is applied elementwise to the output of each artificial “neuron”).

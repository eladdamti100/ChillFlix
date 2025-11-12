# Netflix-part-3

## Overview

This project establishes the server-side logic and architecture for Netflix, focusing on the RESTful API functionality and database interactions. The application is built on Node.js using the MVC architecture to ensure scalability and maintainability. All data is stored in MongoDB, and a connection has been implemented to integrate the recommendation system from the previous exercise via a client-server model. 

The server exclusively returns JSON responses, as rendering HTML is not relevant for an API implementation.

## Installation and Setup

### Prerequisites

1. Install [npm](https://www.npmjs.com/):
   ```bash
   cd src/MongoServer
   npm install
   ```

2. Install [Docker Desktop](https://www.docker.com/products/docker-desktop/).
3. Install [MongoDB Compass](https://www.mongodb.com/products/compass) for managing the database.
4. Install the [Thunder Client extension](https://www.thunderclient.com/) for testing RESTful APIs conveniently in VS Code.

### Environment Variables

Ensure the following environment variables are set in the `.env.local` file located in `./src/MongoServer/config/`:
(You can modify the PORT variable to a different value if you'd like to change the port on which the server runs.)
```env
CONNECTION_STRING="mongodb://mongo:27017/api"
PORT=8181

RECOMMEND_PORT=8081
RECOMMEND_HOST="host.docker.internal"
```

### Running the Project

1. Start Docker Desktop and MongoDB Compass.

2. To start the server and database using Docker Compose, run the following command in the root directory of the project:
   ```bash
   docker compose -f docker-compose.yml --env-file ./src/MongoServer/config/.env.local up --build
   ```

   **Output Example:**
   The following image shows the terminal output when the Docker environment successfully initializes the server and connects to both MongoDB and the recommendation system:
   ![צילום מסך 2025-01-09 215302](https://github.com/user-attachments/assets/33f1c15e-117c-4a39-b042-c2f6c59ce5b8)



3. To run it again after stop use:
   ```bash
   docker compose -f docker-compose.yml --env-file ./src/MongoServer/config/.env.local up
   ```

## How to Use

### API Endpoints

#### Users API

1. **Create a new user**
   - **Endpoint**: `http://localhost:8181/api/users`
   - **Method**: POST
   - **Description**: Creates a new user. The request body should include `username`, `password`, and other user details.
  - **Example Requests**:

     **Admin User (Cristiano Ronaldo)**
     The following request creates a user with admin privileges. Admins can create categories and movies.
     
     ![צילום מסך 2025-01-09 220336](https://github.com/user-attachments/assets/910c893c-18d7-4b3c-b032-36dddf0eba4b)

     **Regular User**
     The following request creates a regular user without admin privileges. Regular users cannot create categories or movies.
     
     ![צילום מסך 2025-01-09 220130](https://github.com/user-attachments/assets/35e2761e-a50b-4887-b769-6a5cc5ba6cb8)

   - **Response Examples**:
     - `201 Created` if the user is successfully created.
     - Example response for admin user creation:
       ```json
       {
         "message": "User created successfully",
         "user": {
           "name": "Cristiano Ronaldo",
           "short_id": 7,
           "email": "phenoman@football.com",
           "phone": "7",
           "username": "waitForIt",
           "password": "siiiiiiiiiii",
           "isAdmin": true,
           "watchlist": {},
           "_id": "678828bfbe3e1734b34752",
           "createdAt": "2025-01-09T20:03:27.212Z",
           "updatedAt": "2025-01-09T20:03:27.212Z",
           "__v": 0
         }
       }
2. **Get user details**
   - **Endpoint**: `http://localhost:8181/api/users/:id`
   - **Method**: GET
   - **Description**: Fetches details of a user by their ID.
   - **Example Response**:
     ```json
      {
        "_id": "67802b8fbe30e1734034a752",
        "name": "Cristiano Ronaldo",
        "short_id": 7,
        "email": "phenoman@Football.com",
        "phone": "7",
        "profilePicture": "",
        "username": "waitForIt",
        "password": "siiiiiiiiiiii",
        "isAdmin": true,
        "watchlist": {
          "101": "67802d52be30e1734034a757",
          "102": "67802d60be30e1734034a760",
          "103": "67802d7fbe30e1734034a765"
        },
        "createdAt": "2025-01-09T20:03:27.212Z",
        "updatedAt": "2025-01-09T20:41:47.246Z",
        "__v": 0
      }
     ```
     
3. **Authenticate user**
   - **Endpoint**: `http://localhost:8181/api/tokens`
   - **Method**: POST 
   - **Description**: Authenticates a user by verifying their username and password. Authentication is required for all subsequent actions, such as creating movies or categories.
   - **Example Request**:
     The request must include the user's ID in the `Authorization` header.
     
     ![צילום מסך 2025-01-09 220656](https://github.com/user-attachments/assets/8f20b41b-7b8f-4c27-ac0e-3aaf8c588578)

   - **Response Example**:
     ```json
     {
       "id": "678828bfbe3e1734b34752"
     }
     ```

   - **Note**: This ID must be included in all subsequent requests in the `Authorization` header for the user to perform authorized actions.
  
4. **Get all users**
   - **Endpoint**: `http://localhost:8181/api/users/all`
   - **Method**: GET
   - **Description**: Retrieves all users in the system. This action requires authentication and is restricted to admin users only.
   - **Example Request**:
     The request must include the user's `Authorization` header.
   - **Response Example**:
     ```json
     {
       "userCount": 2,
       "users": [
         {
           "_id": "67802b0bbe30e1734034a750",
           "name": "Leo Messi",
           "username": "goat",
           "isAdmin": false
         },
         {
           "_id": "67802b8fbe30e1734034a752",
           "name": "Cristiano Ronaldo",
           "username": "waitForIt",
           "isAdmin": true
         }
       ]
     }
     ```
   - **Note**: Non-admin users attempting this action will receive an authorization error.

#### Categories API

> **Note**: For all category-related endpoints, you must be authenticated. Pass the user ID in the `Authorization` header.



1. **Get all categories**
   - **Endpoint**: `http://localhost:8181/api/categories`
   - **Method**: GET
   - **Description**: Retrieves all categories.

2. **Create a new category**
   - **Endpoint**: `http://localhost:8181/api/categories`
   - **Method**: POST
   - **Description**: Creates a new category. This action requires authentication and is restricted to admin users only.
   - **Example Request**:
     The request must include the category name and a `promoted` status in the body, along with the user's `Authorization` header.
     
     ![צילום מסך 2025-01-09 221448](https://github.com/user-attachments/assets/8fe03a85-aab1-4b36-8e60-0730901e4b95)

   - **Response Example**:
     ```json
     {
       "name": "Legends of Football",
       "promoted": true,
       "_id": "678028bfbe3e1734034a775",
       "createdAt": "2025-01-09T20:14:39.559Z",
       "updatedAt": "2025-01-09T20:14:39.559Z",
       "__v": 0
     }
     ```

   - **Note**: Non-admin users attempting this action will receive an authorization error.

3. **Get category by ID**
   - **Endpoint**: `http://localhost:8181/api/categories/:id`
   - **Method**: GET
   - **Description**: Fetches details of a category by its ID.

4. **Update category**
   - **Endpoint**: `http://localhost:8181/api/categories/:id`
   - **Method**: PATCH
   - **Description**: Updates details of a category.

5. **Delete category**
   - **Endpoint**: `http://localhost:8181/api/categories/:id`
   - **Method**: DELETE
   - **Description**: Deletes a category by ID.

#### Movies API

> **Note**: For all movie-related endpoints, you must be authenticated. Pass the user ID in the `Authorization` header.



1. **Get movies by category**
   - **Endpoint**: `http://localhost:8181/api/movies`
   - **Method**: GET
   - **Description**: Retrieves movies by categories, including promoted categories and recently watched movies.


2. **Create a new movie**
   - **Endpoint**: `http://localhost:8181/api/movies`
   - **Method**: POST
   - **Description**: Adds a new movie to the database. This action requires authentication and is restricted to admin users only.
   - **Example Request**:
     The request must include the movie details in the body, along with the user's `Authorization` header.
     
     ![צילום מסך 2025-01-09 221945](https://github.com/user-attachments/assets/ae01d238-4530-4a8a-9e98-1918ccfde170)

   - **Response Example**:
     ```json
     {
       "short_id": 102,
       "title": "Ronaldo vs Messi - The Greatest Rivalry",
       "releaseYear": "2020",
       "description": "An in-depth look at the legendary rivalry between Cristiano Ronaldo and Lionel Messi, exploring their unique skills, achievements, and mutual respect.",
       "age_Rating": {
         "age": "PG",
         "description": ["Sports", "Rivalry"]
       },
       "actors": ["Cristiano Ronaldo", "Lionel Messi"],
       "creators": ["David Tryhorn"],
       "genres": ["Documentary", "Sports"],
       "poster": "https://example.com/ronaldo_vs_messi_poster.jpg",
       "image": "https://example.com/ronaldo_vs_messi_bg.jpg",
       "trailer": "https://youtube.com/trailer_ronaldo_vs_messi",
       "isSeries": false,
       "duration": "1h 30m",
       "_id": "67882d60b8e30e1734034a760",
       "createdAt": "2025-01-09T20:12:12.185Z",
       "updatedAt": "2025-01-09T20:12:12.185Z",
       "__v": 0
     }
     ```

   - **Note**: Non-admin users attempting this action will receive an authorization error.

3. **Get movie details**
   - **Endpoint**: `http://localhost:8181/api/movies/:id`
   - **Method**: GET
   - **Description**: Fetches details of a specific movie by its ID.
   - 
4. **Get all movies**
   - **Endpoint**: `http://localhost:8181/api/movies/all`
   - **Method**: GET
   - **Description**: Retrieves all movies in the system. This action requires authentication and is restricted to admin users only.
   - **Example Request**:
     The request must include the user's `Authorization` header.
   - **Response Example**:
     ```json
     {
       "movieCount": 2,
       "movies": [
         {
           "_id": "678028bfbe3e1734034a775",
           "title": "Ronaldo vs Messi - The Greatest Rivalry"
         },
         {
           "_id": "678028bfbe3e1734034a776",
           "title": "Legend of Messi"
         }
       ]
     }

5. **Update movie**
   - **Endpoint**: `http://localhost:8181/api/movies/:id`
   - **Method**: PUT
   - **Description**: Updates an existing movie.

6. **Delete movie**
   - **Endpoint**: `http://localhost:8181/api/movies/:id`
   - **Method**: DELETE
   - **Description**: Deletes a movie by ID.

#### Recommendations API

1. **Get recommendations for a movie**
   - **Endpoint**: `http://localhost:8181/api/movies/:id/recommend`
   - **Method**: GET
   - **Description**: Fetches recommendations for a specific movie from the recommendation server. This action requires authentication.
   - **Example Request**:
     The request must include the `id` of the movie in the URL and the user's `Authorization` header.
     
     ![צילום מסך 2025-01-09 224426](https://github.com/user-attachments/assets/7ae834fe-7846-41d0-b957-f14f94cfccba)

   - **Response Example**:
     ```json
     {
       "MovieRecommendations": [
         "101",
         "103"
       ]
     }

2. **Add a movie to the recommendation server**
   - **Endpoint**: `http://localhost:8181/api/movies/:id/recommend`
   - **Method**: POST
   - **Description**: Adds a specific movie to the recommendation server. This action requires authentication.
   - **Example Request**:
     The request must include the `id` of the movie in the URL and the user's `Authorization` header.
     
    ![צילום מסך 2025-01-09 223946](https://github.com/user-attachments/assets/f200c510-3711-4ab9-85d7-ec1b172d7776)

   - **Response Example**:
     ```json
     {
       "message": "Created",
       "data": "201 Created"
     }
     ```

   - **Note**: Ensure that the movie exists in the database before attempting to add it to the recommendation server.

#### Search API

**Search for movies by keyword**
   - **Endpoint**: `http://localhost:8181/api/movies/search/:keyword`
   - **Method**: GET
   - **Description**: Searches the movie database for movies containing the specified keyword in their details. This action requires authentication.
   - **Example Request**:
     The request must include the `keyword` in the URL and the user's `Authorization` header.
     
     ![צילום מסך 2025-01-09 224643](https://github.com/user-attachments/assets/c8479ad0-12db-4df5-9c27-68d3ab9aea0b)

   - **Response Example**:
     ```json
     {
       "movieCount": 4,
       "movieList": [
         {
           "_id": "67802d52be30e1734034a757"
         },
         {
           "_id": "67802d60be30e1734034a768"
         },
         {
           "_id": "67802d7fbe30e1734034a765"
         },
         {
           "_id": "67802df5be30e1734034a76e"
         }
       ]
     }
### Example API Calls

You can use the following tools to test API calls:
- **Thunder Client** (in VS Code)
- **Postman**
- **Terminal** (using `curl` or similar tools)

For each endpoint, ensure the appropriate headers and request body are set as described above.


## Additional Notes

- Ensure that the server and MongoDB are running before making any API calls.
- Use `Docker logs` to troubleshoot any issues with the containers. that in `/data/db/mongo.log` in the `MongoDB` Container

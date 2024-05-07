from pprint import pprint
from dataclasses import dataclass
from flask import Flask, redirect, url_for, request, render_template 
app = Flask(__name__, static_url_path='/templates')

COUNTER = 0

# /posts
# GET /posts -> dame todos los posts
# GET /posts/1 -> dame el post con identificador 1
# POST /posts -> creame un post nuevo
# DELETE /posts/post_id -> borrame el post con id post_id

# Posts
# - id, title, text
# /posts
# 	- GET
# 	- POST
# 	- DELETE

POSTS = {}

@dataclass
class Post:
    id: int
    title: str
    text: str

    def __repr__(self):
        return f"{str(self.id)} {self.title} {self.text}"

@app.route('/posts', methods=['POST','GET','DELETE'])
def posts():
    global POSTS
    if request.method == 'GET':
        beginning = """
            <html>
               <body>
                  <form action = "http://127.0.0.1:8000/posts" method = "post">
                     <p>Enter post to create:</p>
                     <p><input type = "text" name = "title" /></p>
                     <p><input type = "text" name = "text" /></p>
                     <p><input type = "submit" value = "submit" /></p>
                  </form>
                  <ul>
                  """
        middle = ""
        for post in POSTS.values():
            middle += "<li>" + str(post) + "</li>"
            print(post)
        end = """
                    </ul>
               </body>
            </html>
        """
        pprint(POSTS)

        return beginning + middle + end
    elif request.method == 'POST':
        # procesamiento del request, extraccion de parametros, validacion
        title = request.form['title']
        text = request.form['text']

        # datos y almacenamiento
        post_id = len(POSTS.keys())

        # creacion del posteo
        post = Post(post_id, title, text)

        # guardado del posteo 
        POSTS[post_id] = post
        
        print(POSTS)
        # generacion de la respuesta
        return redirect(url_for('posts'))
    elif request.method == 'DELETE':
        post_id = int(request.args['id'])
        POSTS.pop(post_id)
        return redirect(url_for('posts'))
    else:
        return "Unknown method"
    
@app.route('/counter')
def counter():
    global COUNTER
    if request.method == 'GET':
        COUNTER += 1
    return "OK" + str(COUNTER)

@app.route('/success/<name>')
def success(name):
   return f'welcome {name}'

@app.route('/login', methods = ['POST', 'GET'])
def login():
   if request.method == 'GET':
       return render_template('login.html')
   if request.method == 'POST':
      user = request.form['nm']
      location = url_for('success',name = user)
      print(f"REDIRECT: {location}")
      return redirect(location)
   else:
      user = request.args.get('nm')
      return redirect(url_for('success',name = user))

@app.route('/')
def index():
    html = """
    <ul>
    <li><a href='http://127.0.0.1:8000/login'>login</a></li>
    <li><a href='http://127.0.0.1:8000/counter'>counter</a></li>
    <li><a href='http://127.0.0.1:8000/posts'>posts</a></li>
    </ul>
    """
    return html

if __name__ == '__main__':
   app.run(host="127.0.0.1", port=8000, debug = True)


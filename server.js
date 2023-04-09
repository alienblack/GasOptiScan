

const express = require('express');
const { spawn } = require('child_process');
const bodyParser = require('body-parser');
const cors = require('cors');
const fs = require('fs');

const app = express();
const port = 8080;
app.use(cors());
app.use(bodyParser.json());


// app.post('/run_cpp_code', (req, res) => {
//   console.log(req.body.code, "code");
//   let solidityCode = req.body.code;
//   console.log(solidityCode,"solidity");

//   // Compile and run a C++ program
//   const child = spawn('g++', ['main.cpp', '-main', 'main']);
//   child.stdout.on('data', (data) => {
//     console.log(`stdout: ${data}`);
//   });
//   child.stderr.on('data', (data) => {
//     console.error(`stderr: ${data}`);
//   });

//   let output = '';

//   child.on('close', (code) => {
//     console.log(`child process exited with code ${code}`);
//     const cp = spawn('./main');
//     cp.stdout.on('data', (data) => {
//       console.log(`cp stdout: ${data}`);
//       output += data;
//     });
//     cp.on('close', () => {
//       console.log("Output : "+output)
//       res.send(output);
//     });
//   });
// });


app.post('/run_cpp_code', (req, res) => {
  console.log(req.body.code, "code");
  let solidityCode = req.body.code;
  console.log(solidityCode,"solidity");

  // Write the solidity code to a file named code.sol
  fs.writeFile('code.sol', solidityCode, (err) => {
    if (err) {
      console.error(err);
      res.status(500).send('Error writing file');
    } else {
      console.log('Solidity code written to file');
      // Compile and run a C++ program
      const child = spawn('g++', ['main.cpp', '-main', 'main']);
      child.stdout.on('data', (data) => {
        console.log(`stdout: ${data}`);
      });
      child.stderr.on('data', (data) => {
        console.error(`stderr: ${data}`);
      });

      let output = '';

      child.on('close', (code) => {
        console.log(`child process exited with code ${code}`);
        const cp = spawn('./main');
        cp.stdout.on('data', (data) => {
          console.log(`cp stdout: ${data}`);
          output += data;
        });
        cp.on('close', () => {
          console.log("Output : "+output)
          res.send(output);
        });
      });
    }
  });
});




// app.post('/run_cpp_code', (req, res) => {
//   console.log(req.body.code, "code");
//   let solidityCode = req.body.code;
//   console.log(solidityCode,"solidity");
//   // Compile and run a C++ program
//   const child = spawn('g++', ['cp.cpp', '-o', 'cp']);
//   child.stdout.on('data', (data) => {
//     console.log(`stdout: ${data}`);
//   });

//   child.stderr.on('data', (data) => {
//     console.error(`stderr: ${data}`);
//   });
//   let output = '';

//   child.on('close', (code) => {
//     console.log(`child process exited with code ${code}`);
//     const cp = spawn('./cp');
//     cp.stdout.on('data', (data) => {
//       console.log(`cp stdout: ${data}`);
//       output += data;
//       console.log("Output : "+data)
//       res.send(data);
//     });
    
//     // cp.on('close', () => {
//       // res.send(output);
//     // });
//   });



// // return res.json({"msg" : output});
// });

// app.all('*', (req, res) => {
//   res.status(404).send('Not found');
// });

app.listen(port, () => {
  console.log(`App listening at http://localhost:${port}`);
});

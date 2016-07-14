const cluster = require('cluster');
const http = require('http');
var sleep = require('thread-sleep');
const numWorkers = 128;
var locks = require('locks');
var fs = require('fs');
var times = 0;
var timesWrote = 0;
var x = 100;

if (cluster.isMaster) {

  // Variable Declaration
  var queue = [];
  var mutex = locks.createMutex();
  var vez = 0;
  var done = Array(numWorkers+1).fill(false);
  console.log('processos: ' + numWorkers);



  // Handles Request and Release messages
  function messageHandler(msg) {
    if (msg.cmd && msg.cmd == 'request') {
      //console.log(msg);
      fs.appendFile("log.txt", "id = " + msg.id + " - request : " + new Date().getTime() + "\n", function(err) {
        if (err) {
          //console.log(err); 
        }
        queue.push(msg.id);
      });
    }
    if (msg.cmd && msg.cmd == 'release') {
      fs.appendFile("log.txt", "id = " + msg.id + " - release : " + new Date().getTime() + "\n", function(err) {
        if (err) {
          //console.log(err); 
        }
        mutex.unlock();
      //console.log('liberei o lock');
      });
    }
  }

  // Handles closing when all workers are done
  function checkIfDone(id){
    done[id] = true;
    for (i = 1; i < done.length; i++) { 
      if(!done[i]){
        return;
      }
    }
    process.exit(0);
  }

  // Keep running function to check the queue
  setInterval(function(){ 
    if(queue.length > 0) {
      //console.log('fila');
      if (mutex.tryLock()) {
        //console.log('We got the lock!');
        vez = queue.shift();
        fs.appendFile("log.txt", "id = master - grant : " + new Date().getTime() + "\n", function(err) {
          if (err) {
            //console.log(err); 
          }
          cluster.workers[vez].send({id: 'master', cmd: 'grant'});
        });
      }
    }
  }, 0);

      // Start workers
      for (var i = 0; i < numWorkers; i++) {
        cluster.fork();
        var delay = Math.round(Math.random()*1000);
        sleep(delay);
      }

  

  Object.keys(cluster.workers).forEach((id) => {
    cluster.workers[id].on('message', messageHandler);
    cluster.workers[id].on('disconnect', () => {checkIfDone(id)});
  });
  
} else {
  // notify master about the request
  function request(){
    process.send({ id: cluster.worker.id, cmd: 'request' });
    times += 1;
    //console.log(times);

    if ( times < x){
     setTimeout(function(){ 
        request();
      }, (Math.random()*1000)); 
    }
  }
  
  request();

  process.on('message', (msg) => {
    if(msg.id && msg.cmd && msg.id == 'master' && msg.cmd == 'grant'){
      fs.appendFile("test.txt", "frase\n", function(err) {
        if (err) {
          //console.log(err); 
        }
        //console.log('escrevi no arquivo');
        timesWrote += 1;
        process.send({ id: cluster.worker.id, cmd: 'release', lock: msg.lock});
        if( times >= x && timesWrote >= x){
          cluster.worker.disconnect();
        }
      }); 
    }   
  });
    
}
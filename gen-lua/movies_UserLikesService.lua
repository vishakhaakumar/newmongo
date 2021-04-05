--
-- Autogenerated by Thrift
--
-- DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
-- @generated
--


require 'Thrift'
require 'movies_ttypes'

UserLikesServiceClient = __TObject.new(__TClient, {
  __type = 'UserLikesServiceClient'
})

function UserLikesServiceClient:GetMovieLikesByIds(movie_ids)
  self:send_GetMovieLikesByIds(movie_ids)
  return self:recv_GetMovieLikesByIds(movie_ids)
end

function UserLikesServiceClient:send_GetMovieLikesByIds(movie_ids)
  self.oprot:writeMessageBegin('GetMovieLikesByIds', TMessageType.CALL, self._seqid)
  local args = GetMovieLikesByIds_args:new{}
  args.movie_ids = movie_ids
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function UserLikesServiceClient:recv_GetMovieLikesByIds(movie_ids)
  local fname, mtype, rseqid = self.iprot:readMessageBegin()
  if mtype == TMessageType.EXCEPTION then
    local x = TApplicationException:new{}
    x:read(self.iprot)
    self.iprot:readMessageEnd()
    error(x)
  end
  local result = GetMovieLikesByIds_result:new{}
  result:read(self.iprot)
  self.iprot:readMessageEnd()
  if result.success ~= nil then
    return result.success
  end
  error(TApplicationException:new{errorCode = TApplicationException.MISSING_RESULT})
end

function UserLikesServiceClient:LikeDislikeMovie(user_id, movie_id, likeDislike)
  self:send_LikeDislikeMovie(user_id, movie_id, likeDislike)
  self:recv_LikeDislikeMovie(user_id, movie_id, likeDislike)
end

function UserLikesServiceClient:send_LikeDislikeMovie(user_id, movie_id, likeDislike)
  self.oprot:writeMessageBegin('LikeDislikeMovie', TMessageType.CALL, self._seqid)
  local args = LikeDislikeMovie_args:new{}
  args.user_id = user_id
  args.movie_id = movie_id
  args.likeDislike = likeDislike
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function UserLikesServiceClient:recv_LikeDislikeMovie(user_id, movie_id, likeDislike)
  local fname, mtype, rseqid = self.iprot:readMessageBegin()
  if mtype == TMessageType.EXCEPTION then
    local x = TApplicationException:new{}
    x:read(self.iprot)
    self.iprot:readMessageEnd()
    error(x)
  end
  local result = LikeDislikeMovie_result:new{}
  result:read(self.iprot)
  self.iprot:readMessageEnd()
end
UserLikesServiceIface = __TObject:new{
  __type = 'UserLikesServiceIface'
}


UserLikesServiceProcessor = __TObject.new(__TProcessor
, {
 __type = 'UserLikesServiceProcessor'
})

function UserLikesServiceProcessor:process(iprot, oprot, server_ctx)
  local name, mtype, seqid = iprot:readMessageBegin()
  local func_name = 'process_' .. name
  if not self[func_name] or ttype(self[func_name]) ~= 'function' then
    iprot:skip(TType.STRUCT)
    iprot:readMessageEnd()
    x = TApplicationException:new{
      errorCode = TApplicationException.UNKNOWN_METHOD
    }
    oprot:writeMessageBegin(name, TMessageType.EXCEPTION, seqid)
    x:write(oprot)
    oprot:writeMessageEnd()
    oprot.trans:flush()
  else
    self[func_name](self, seqid, iprot, oprot, server_ctx)
  end
end

function UserLikesServiceProcessor:process_GetMovieLikesByIds(seqid, iprot, oprot, server_ctx)
  local args = GetMovieLikesByIds_args:new{}
  local reply_type = TMessageType.REPLY
  args:read(iprot)
  iprot:readMessageEnd()
  local result = GetMovieLikesByIds_result:new{}
  local status, res = pcall(self.handler.GetMovieLikesByIds, self.handler, args.movie_ids)
  if not status then
    reply_type = TMessageType.EXCEPTION
    result = TApplicationException:new{message = res}
  else
    result.success = res
  end
  oprot:writeMessageBegin('GetMovieLikesByIds', reply_type, seqid)
  result:write(oprot)
  oprot:writeMessageEnd()
  oprot.trans:flush()
end

function UserLikesServiceProcessor:process_LikeDislikeMovie(seqid, iprot, oprot, server_ctx)
  local args = LikeDislikeMovie_args:new{}
  local reply_type = TMessageType.REPLY
  args:read(iprot)
  iprot:readMessageEnd()
  local result = LikeDislikeMovie_result:new{}
  local status, res = pcall(self.handler.LikeDislikeMovie, self.handler, args.user_id, args.movie_id, args.likeDislike)
  if not status then
    reply_type = TMessageType.EXCEPTION
    result = TApplicationException:new{message = res}
  else
    result.success = res
  end
  oprot:writeMessageBegin('LikeDislikeMovie', reply_type, seqid)
  result:write(oprot)
  oprot:writeMessageEnd()
  oprot.trans:flush()
end

-- HELPER FUNCTIONS AND STRUCTURES

GetMovieLikesByIds_args = __TObject:new{
  movie_ids
}

function GetMovieLikesByIds_args:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.LIST then
        self.movie_ids = {}
        local _etype21, _size18 = iprot:readListBegin()
        for _i=1,_size18 do
          local _elem22 = iprot:readString()
          table.insert(self.movie_ids, _elem22)
        end
        iprot:readListEnd()
      else
        iprot:skip(ftype)
      end
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function GetMovieLikesByIds_args:write(oprot)
  oprot:writeStructBegin('GetMovieLikesByIds_args')
  if self.movie_ids ~= nil then
    oprot:writeFieldBegin('movie_ids', TType.LIST, 1)
    oprot:writeListBegin(TType.STRING, #self.movie_ids)
    for _,iter23 in ipairs(self.movie_ids) do
      oprot:writeString(iter23)
    end
    oprot:writeListEnd()
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

GetMovieLikesByIds_result = __TObject:new{
  success
}

function GetMovieLikesByIds_result:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 0 then
      if ftype == TType.LIST then
        self.success = {}
        local _etype27, _size24 = iprot:readListBegin()
        for _i=1,_size24 do
          local _elem28 = iprot:readI64()
          table.insert(self.success, _elem28)
        end
        iprot:readListEnd()
      else
        iprot:skip(ftype)
      end
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function GetMovieLikesByIds_result:write(oprot)
  oprot:writeStructBegin('GetMovieLikesByIds_result')
  if self.success ~= nil then
    oprot:writeFieldBegin('success', TType.LIST, 0)
    oprot:writeListBegin(TType.I64, #self.success)
    for _,iter29 in ipairs(self.success) do
      oprot:writeI64(iter29)
    end
    oprot:writeListEnd()
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

LikeDislikeMovie_args = __TObject:new{
  user_id,
  movie_id,
  likeDislike
}

function LikeDislikeMovie_args:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.STRING then
        self.user_id = iprot:readString()
      else
        iprot:skip(ftype)
      end
    elseif fid == 2 then
      if ftype == TType.STRING then
        self.movie_id = iprot:readString()
      else
        iprot:skip(ftype)
      end
    elseif fid == 3 then
      if ftype == TType.BOOL then
        self.likeDislike = iprot:readBool()
      else
        iprot:skip(ftype)
      end
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function LikeDislikeMovie_args:write(oprot)
  oprot:writeStructBegin('LikeDislikeMovie_args')
  if self.user_id ~= nil then
    oprot:writeFieldBegin('user_id', TType.STRING, 1)
    oprot:writeString(self.user_id)
    oprot:writeFieldEnd()
  end
  if self.movie_id ~= nil then
    oprot:writeFieldBegin('movie_id', TType.STRING, 2)
    oprot:writeString(self.movie_id)
    oprot:writeFieldEnd()
  end
  if self.likeDislike ~= nil then
    oprot:writeFieldBegin('likeDislike', TType.BOOL, 3)
    oprot:writeBool(self.likeDislike)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

LikeDislikeMovie_result = __TObject:new{

}

function LikeDislikeMovie_result:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function LikeDislikeMovie_result:write(oprot)
  oprot:writeStructBegin('LikeDislikeMovie_result')
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end
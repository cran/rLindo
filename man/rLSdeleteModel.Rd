\name{rLSdeleteModel}
\alias{rLSdeleteModel}

\title{Delete LINDO API model object.}

\description{
 R interface function for LINDO API function \code{LSdeleteModel}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 The memory used by the model object is freed. 
}

\usage{
rLSdeleteModel(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLScreateModel}}
}

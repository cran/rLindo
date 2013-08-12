\name{rLSloadVarType}
\alias{rLSloadVarType}

\title{Load variable type data into a model structure.}

\description{
 R interface function for LINDO API function \code{LSloadVarType}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSloadVarType(model,spszVarTypes)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{spszVarTypes}{A character array containing the type of each variable. Valid values for each variable are 'C', 'B', or 'I' for continuous, binary, or general integer, respectively.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
